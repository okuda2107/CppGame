#include "Mesh.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include <fstream>
#include <sstream>
#include <document.h>
#include <SDL_log.h>
#include "Math.h"

Mesh::Mesh()
	:mVertexArray(nullptr)
	, mRadius(0.0f)
	, mSpecPower(100.0f)
{}

Mesh::~Mesh()
{}

bool Mesh::Load(const std::string& fileName, Renderer* renderer)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Mesh %s", fileName.c_str());
		return false;
	}
	if (this->LoadJSON(fileName, renderer)) return true;
	else if (this->LoadObj(fileName, renderer)) return true;
	
	return false;
}

bool Mesh::LoadJSON(const std::string& fileName, Renderer* renderer) {
	std::ifstream file(fileName);
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		SDL_Log("Mesh %s is not valid json", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the version
	if (ver != 1)
	{
		SDL_Log("Mesh %s not version 1", fileName.c_str());
		return false;
	}

	mShaderName = doc["shader"].GetString();

	// Skip the vertex format/shader for now
	// (This is changed in a later chapter's code)
	size_t vertSize = 8;

	// Load textures
	const rapidjson::Value& textures = doc["textures"];
	if (!textures.IsArray() || textures.Size() < 1)
	{
		SDL_Log("Mesh %s has no textures, there should be at least one", fileName.c_str());
		return false;
	}

	mSpecPower = static_cast<float>(doc["specularPower"].GetDouble());

	for (rapidjson::SizeType i = 0; i < textures.Size(); i++)
	{
		// Is this texture already loaded?
		std::string texName = textures[i].GetString();
		Texture* t = renderer->GetTexture(texName);
		if (t == nullptr)
		{
			// Try loading the texture
			t = renderer->GetTexture(texName);
			if (t == nullptr)
			{
				// If it's still null, just use the default texture
				t = renderer->GetTexture("Assets/Default.png");
			}
		}
		mTextures.emplace_back(t);
	}

	// Load in the vertices
	const rapidjson::Value& vertsJson = doc["vertices"];
	if (!vertsJson.IsArray() || vertsJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no vertices", fileName.c_str());
		return false;
	}

	std::vector<float> vertices;
	vertices.reserve(vertsJson.Size() * vertSize);
	mRadius = 0.0f;
	for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
	{
		// For now, just assume we have 8 elements
		const rapidjson::Value& vert = vertsJson[i];
		if (!vert.IsArray() || vert.Size() != 8)
		{
			SDL_Log("Unexpected vertex format for %s", fileName.c_str());
			return false;
		}

		Vector3 pos(vert[0].GetDouble(), vert[1].GetDouble(), vert[2].GetDouble());
		mRadius = Math::Max(mRadius, pos.LengthSq());

		// Add the floats
		for (rapidjson::SizeType i = 0; i < vert.Size(); i++)
		{
			vertices.emplace_back(static_cast<float>(vert[i].GetDouble()));
		}
	}

	// We were computing length squared earlier
	mRadius = Math::Sqrt(mRadius);

	// Load in the indices
	const rapidjson::Value& indJson = doc["indices"];
	if (!indJson.IsArray() || indJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no indices", fileName.c_str());
		return false;
	}

	std::vector<unsigned int> indices;
	indices.reserve(indJson.Size() * 3);
	for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
	{
		const rapidjson::Value& ind = indJson[i];
		if (!ind.IsArray() || ind.Size() != 3)
		{
			SDL_Log("Invalid indices for %s", fileName.c_str());
			return false;
		}

		indices.emplace_back(ind[0].GetUint());
		indices.emplace_back(ind[1].GetUint());
		indices.emplace_back(ind[2].GetUint());
	}

	// Now create a vertex array
	mVertexArray = new VertexArray(vertices.data(), static_cast<unsigned>(vertices.size()) / vertSize,
		indices.data(), static_cast<unsigned>(indices.size()));
	return true;
}

bool Mesh::LoadObj(const std::string& fileName, Renderer* renderer) {
	std::fstream file(fileName);
	
	while (!file.eof()) {
		//　1行読み取り
        file.getline()

        //　バッファの1文字目で判別
        switch ( buf[0] )
        {
        case 'v':
            //　バッファの2文字目で判別
            switch ( buf[1] )
            {
            //　Vertex
            case ' ':
                //　頂点座標を読み取り
                if ( sscanf(buf+2, "%f %f %f %f", &tmp_vert.x, &tmp_vert.y, &tmp_vert.z, &tmp_float) != 4 )
                {
                    if ( sscanf(buf+2, "%f %f %f", &tmp_vert.x, &tmp_vert.y, &tmp_vert.z) != 3 )
                    {
                        cout << "Error : 頂点座標の数が不正です\n";
                        return false;
                    }
                }
                //　初期値の設定
                if ( !size_flag )
                {
                    min_size = tmp_vert.x;
                    max_size = tmp_vert.x;
                    size_flag = true;
                }
                //　最大・最小の比較
                for ( int i=0; i<3; i++ )
                {
                    if ( min_size > tmp_vert.v[i] ) min_size = tmp_vert.v[i];
                    if ( max_size < tmp_vert.v[i] ) max_size = tmp_vert.v[i];
                }
                //　頂点座標を追加
                AddVertex(tmp_vert);
                break;

            //　Normal
            case 'n':
                //　法線ベクトルの読み取り
                if ( sscanf(buf+2, "%f %f %f", &tmp_norm.x, &tmp_norm.y, &tmp_norm.z) != 3)
                {
                    cout << "Error : 法線ベクトルの数が不正です\n";
                    return false;
                }
                //　法線ベクトルを追加
                AddNormal(tmp_norm);
                break;
            }
            break;

        //　face
        case 'f':
            pbuf = buf;
            //　空白の数で要素数がいくつあるかカウント
            while ( *pbuf )
            {
                if ( *pbuf == ' ' ) tmp_face.element++;
                pbuf++;
            }
            //　要素数3未満なら面を構成できない
            if ( tmp_face.element < 3 )
            {
                cout << "Error : 面を構成するための要素数が不正です\n";
                return false;
            }
            switch ( tmp_face.element )
            {
            //　三角形
            case 3:
                tmp_face.type = GL_TRIANGLES;
                break;

            //　四角形
            case 4:
                tmp_face.type = GL_QUADS;
                break;

            //　多角形
            default:
                tmp_face.type = GL_POLYGON;
                break;
            }
            //　インデックス用のメモリを確保
            tmp_face.vertex_index = new int [tmp_face.element];
            tmp_face.normal_index = new int [tmp_face.element];
            pbuf = buf;
            for ( int i=0; i<tmp_face.element; i++ )
            {
                pbuf = strchr(pbuf, ' ');
                pbuf++;

                //　構成要素の読み取り
                if ( sscanf(pbuf, "%d/%d/%d", &tmp_face.vertex_index[i], &tmp_float, &tmp_face.normal_index[i] ) != 3 )
                {
                    if ( sscanf(pbuf, "%d//%d", &tmp_face.vertex_index[i], &tmp_face.normal_index[i] ) != 2 )
                    {
                        if ( sscanf(pbuf, "%d/%d", &tmp_face.vertex_index[i], &tmp_float ) != 2 )
                        {
                            sscanf(pbuf, "%d", &tmp_face.vertex_index[i]);
                            tmp_face.use_normal = false;
                        }
                        else
                        {
                            tmp_face.use_normal = false;
                        }
                    }
                    else
                    {
                        tmp_face.use_normal = true;
                    }
                }
                else
                {
                    tmp_face.use_normal = true;
                }
                //　配列の番号と合わせる
                tmp_face.vertex_index[i]--;
                if ( tmp_face.use_normal ) tmp_face.normal_index[i]--;
            }
            //　マテリアルインデックスを格納
            tmp_face.material_index = cmi;
            //　面を追加
            AddFace(tmp_face);
            break;

        //　usemtl
        case 'u':
            //　マテリアル名を読み取り
            strcpy(tmp_char, " ");
            sscanf(buf, "usemtl %s", &tmp_char);
            //　マテリアル名から検索
            for ( int i=0; i<num_material; i++ )
            {
                //　名前が一致したらマテリアル番号を格納
                if ( strcmpi(material[i].name, tmp_char) == 0 ) cmi = i;
            }
            break;

        //　mtllib
        case 'm':
            //　マテリアルファイル名を読み取り
            strcpy(tmp_char, " ");
            sscanf(buf, "mtllib %s", &tmp_char);
            //　マテリアルファイルの読み込み
            if ( !LoadMTLFile(
                SetDirectoryName(tmp_char, directoryName)   //　ディレクトリを付加
                ))
                return false;
            break;
        
		case '\n':
			break;

        default:
            SDL_Log("Mesh %s is not valid obj file", fileName.c_str());
			return false;
        }
    }

    //　ファイルを閉じる
    file.close();

    return true;
}

void Mesh::Unload()
{
	delete mVertexArray;
	mVertexArray = nullptr;
}

Texture* Mesh::GetTexture(size_t index)
{
	if (index < mTextures.size())
	{
		return mTextures[index];
	}
	else
	{
		return nullptr;
	}
}
