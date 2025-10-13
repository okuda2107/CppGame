#include "Handler.h"

#include "Math.h"
#include "System.h"
#include "api/OpenAL/EventInstance.h"

OpenAL::Handler::Handler(OpenAL::System* system, unsigned int id)
    : mSystem(system), mID(id) {}
OpenAL::Handler::~Handler() {}

// イベントの実体とは外れて存在するapiのため，実体がまだあるかのチェック
bool OpenAL::Handler::IsValid() { return mSystem && mSystem->GetInstance(mID); }

void OpenAL::Handler::Restart() {
    EventInstance* e = mSystem->mInstances.at(mID);
    ALuint source = e->GetSource();
    ALint state = e->GetState();
    if (state == AL_INITIAL) {  // 既に鳴っていたら位置をリセットするのみ
        alSourcePlay(source);
    } else if (state == AL_PLAYING) {
        alSourcePause(source);
        alSourceRewind(source);  // 位置をリセット
        alSourcePlay(source);    // 再生
    } else if (state == AL_PAUSED || state == AL_STOPPED) {
        alSourceRewind(source);  // 位置をリセット
        alSourcePlay(source);    // 再生
    }
}

// todo: フェードアウトはサポートしない．時間があったらする．
void OpenAL::Handler::Stop(bool allowedFadeOut) {
    ALuint source = mSystem->mInstances.at(mID)->GetSource();
    alSourceStop(source);
}

void OpenAL::Handler::SetPaused(bool pause) {
    EventInstance* e = mSystem->mInstances.at(mID);
    ALuint source = e->GetSource();
    ALint state = e->GetState();

    if (pause && state == AL_PLAYING) {
        alSourcePause(source);
    } else if (!pause && state == AL_PAUSED) {
        alSourcePlay(source);
    }
}

void OpenAL::Handler::SetVolume(float volume) {
    ALuint source = mSystem->mInstances.at(mID)->GetSource();
    alSourcef(source, AL_GAIN, volume);
}

void OpenAL::Handler::SetPitch(float value) {
    ALuint source = mSystem->mInstances.at(mID)->GetSource();
    alSourcef(source, AL_PITCH, value);
}

// todo: 他のパラメータ用？
void OpenAL::Handler::SetParameter(const std::string& name, float value) {};

bool OpenAL::Handler::GetPaused() const {
    ALuint source = mSystem->mInstances.at(mID)->GetSource();
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state == AL_PAUSED;
}

float OpenAL::Handler::GetVolume() const {
    ALuint source = mSystem->mInstances.at(mID)->GetSource();
    ALfloat volume;
    alGetSourcef(source, AL_GAIN, &volume);
    return volume;
}

float OpenAL::Handler::GetPitch() const {
    ALuint source = mSystem->mInstances.at(mID)->GetSource();
    ALfloat pitch;
    alGetSourcef(source, AL_PITCH, &pitch);
    return pitch;
}

// todo: 他のパラメータ用？
float OpenAL::Handler::GetParameter(const std::string& name) { return 0.0; }

// イベントが3Dオーディオか？
bool OpenAL::Handler::Is3D() const {
    // イベントの取得
    Event* event = mSystem->mInstances.at(mID)->GetEvent();
    return event->mIs3D;
}

// ワールド行列を受け取って，音声が再生される座標を設定
void OpenAL::Handler::Set3DAttributes(const Matrix4& worldTrans) {
    ALuint source = mSystem->mInstances.at(mID)->GetSource();

    // イベントが3Dオーディオか？
    if (!Is3D()) return;

    // イベントの座標
    Vector3 vec = VecToOpenAL(worldTrans.GetTranslation());
    ALfloat pos[] = {vec.x, vec.y, vec.z};

    // 向いている方向
    // ワールド空間では第1行が前方向
    Vector3 forward = VecToOpenAL(worldTrans.GetXAxis());
    // ワールド空間では第3行が上方向
    Vector3 up = VecToOpenAL(worldTrans.GetZAxis());
    // {front[3], up[3]}，{前方向ベクトル (x, y, z), 上方向ベクトル (x, y,
    // z)}からなる6要素の配列
    ALfloat ori[] = {forward.x, forward.y, forward.z, up.x, up.y, up.z};

    // 速度
    ALfloat vel[] = {0, 0, 0};

    // それぞれ設定
    alSourcefv(source, AL_POSITION, pos);
    alSourcefv(source, AL_ORIENTATION, ori);
    alSourcefv(source, AL_VELOCITY, vel);
}
