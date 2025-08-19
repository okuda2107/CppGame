#include "Handler.h"

#include "Math.h"
#include "System.h"

OpenAL::Handler::Handler(OpenAL::System* system, ALuint source)
    : mSystem(system), mSource(source) {}
OpenAL::Handler::~Handler() {}

bool OpenAL::Handler::IsValid() {
    auto iter = mSystem->mHandlers.find(mSource);
    if (iter != mSystem->mHandlers.end()) {
        return true;
    }
    return false;
}

void OpenAL::Handler::Restart() {
    alSourceRewind(mSource);
    alSourcePlay(mSource);
}

// todo: フェードアウトはサポートしない．時間があったらする．
void OpenAL::Handler::Stop(bool allowedFadeOut) { alSourceStop(mSource); }

void OpenAL::Handler::SetPaused(bool pause) {
    if (pause) {
        alSourcePause(mSource);
    } else {
        alSourcePlay(mSource);
    }
}

void OpenAL::Handler::SetVolume(float volume) {
    alSourcef(mSource, AL_GAIN, volume);
}

void OpenAL::Handler::SetPitch(float value) {
    alSourcef(mSource, AL_PITCH, value);
}

// todo: 他のパラメータ用？
void OpenAL::Handler::SetParameter(const std::string& name, float value) {};

bool OpenAL::Handler::GetPaused() const {
    ALint state;
    alGetSourcei(mSource, AL_SOURCE_STATE, &state);
    return state == AL_PAUSED;
}

float OpenAL::Handler::GetVolume() const {
    ALfloat volume;
    alGetSourcef(mSource, AL_GAIN, &volume);
    return volume;
}

float OpenAL::Handler::GetPitch() const {
    ALfloat pitch;
    alGetSourcef(mSource, AL_PITCH, &pitch);
    return pitch;
}

// todo: 他のパラメータ用？
float OpenAL::Handler::GetParameter(const std::string& name) { return 0.0; }

// イベントが3Dオーディオか？
bool OpenAL::Handler::Is3D() const {
    // イベントの取得
    if (!mSystem) return false;
    auto iter = mSystem->mEvents.find(mEventID);
    if (iter != mSystem->mEvents.end()) {
        return iter->second->mIs3D;
    }
    return false;
}

// ワールド行列を受け取って，音声が再生される座標を設定
void OpenAL::Handler::Set3DAttributes(const Matrix4& worldTrans) {
    // イベントが3Dオーディオか？
    if (!Is3D()) return;

    // イベントの座標
    ALfloat pos[] = VecToOpenAL(worldTrans.GetTranslation());

    // 向いている方向
    // 逆ビューでは第3行が前方向
    Vector3 forward = VecToOpenAL(worldTrans.GetZAxis());
    // 逆ビューでは第2行が上方向
    Vector3 up = VecToOpenAL(worldTrans.GetYAxis());
    // {front[3], up[3]}，{前方向ベクトル (x, y, z), 上方向ベクトル (x, y,
    // z)}からなる6要素の配列
    ALfloat ori[] = {forward, up};

    // 速度
    ALfloat vel[3] = {0, 0, 0};

    // それぞれ設定
    alSourcefv(mSource, AL_POSITION, pos);
    alSourcefv(mSource, AL_ORIENTATION, ori);
    alSourcefv(mSource, AL_VELOCITY, vel);
}

ALint OpenAL::Handler::GetState() const {
    ALint state;
    alGetSourcei(mSource, AL_SOURCE_STATE, &state);
    return state;
}
