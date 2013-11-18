#include "Map.h"
#include "JsonParser.h"

CMap::CMap()
{
	m_pvspLayer = new std::vector<SLayer*>;
	m_pvspTileSet = new std::vector<STileSet*>;
	m_pTiles = new CTile;
}

CMap::~CMap()
{
	for(std::vector<SLayer*>::iterator iter = m_pvspLayer->begin();
		iter != m_pvspLayer->end(); ++ iter)
		this->DestroyLayer(*iter);// ?

	for(std::vector<STileSet*>::iterator iter = m_pvspTileSet->begin();
		iter != m_pvspTileSet->end(); ++ iter) 
		this->DestroyTileset(*iter);

	delete m_pvspLayer;
	delete m_pvspTileSet;
	delete m_pTiles;
}
// Copy from the internet, maybe not safe!
std::wstring s2ws(const std::string& s)
{
    setlocale(LC_ALL, "chs"); 
    const char* _Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, "C");
    return result;
}
bool CMap::LoadMap(IDirect3DDevice9* ipdevice, std::wstring wstrFilePath)
{
try 
{
	CJsonParser jparser;

	jparser.ReadFromFile(wstrFilePath, this);		// Load all information needed into the map object.

	// create a map surface
	m_ipDevice = ipdevice;
	//m_ipDevice->CreateRenderTarget(800, 600, D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE, 0, true, &m_ipMapSurface, NULL);
	if(FAILED(m_ipDevice->CreateOffscreenPlainSurface(800, 600,
		D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &m_ipMapSurface, NULL)))
		MessageBox(NULL, L"Create map surface error!", L"Error", MB_OK);

	// init the tile and texture objects
	m_pTiles->Create(ipdevice, m_iTilesetCount);	// Specific how many texture to create
	for(int index = 0; index < m_iTilesetCount; ++index)
	{
		std::wstringstream wsstream;
		wsstream << L"./Assets/tileset/" << s2ws((*m_pvspTileSet)[index]->image);
		m_pTiles->Load(index, wsstream.str(), (*m_pvspTileSet)[index]->imageWH.width, 
						(*m_pvspTileSet)[index]->imageWH.height, 
						(*m_pvspTileSet)[index]->tileWH.width,
						(*m_pvspTileSet)[index]->tileWH.height, 
						D3DCOLOR_XRGB(0, 255, 255));
	}
}
catch(...)
{
	return false;
}
	return true;
}
// Get How many tiles in a row
int	 CMap::GetMapTileCountW()								
{
	return m_sMapWH.width;
}
// Get How many tiles in a column
int	 CMap::GetMapTileCountH()
{
	return m_sMapWH.height;
}
// Get tile width
int	 CMap::GetTileWidth()
{
	return m_sTileWH.width;
}
// Get tile height
int	 CMap::GetTileHeight()
{
	return m_sTileWH.height;
}
// Set How many tiles in a row
void CMap::SetMapTileCountW(int width)						
{
	m_sMapWH.width = width;
}
// Set How many tiles in a column
void CMap::SetMapTileCountH(int height)
{
	m_sMapWH.height = height;
}
// Set tile width
void CMap::SetTileWidth(int width)
{
	m_sTileWH.width = width;
}
// Set tile height
void CMap::SetTileHeight(int height)
{
	m_sTileWH.height = height;
}
/* Layer information */
int  CMap::GetLayerCount()
{
	return m_iLayerCount;
}
void CMap::SetLayerCount(int layerCount)
{
	m_iLayerCount = layerCount;
}
// Add a new layer, call the build layer method inside
void CMap::AddLayer(std::vector<int>* data, int width, int height, std::string name, std::string type, 
					bool visible, int x, int y)		
{
	m_pvspLayer->push_back( this->BuildLayer(data, width, height, name, type, visible, x, y) );
}
// Build a layer based on the information passed in
CMap::SLayer* CMap::BuildLayer(std::vector<int>* data, int width, int height, std::string name, std::string type, 
					bool visible, int x, int y)		
{
	SLayer* layer			= new SLayer;	// new a layer on heap
	layer->data				= data;
	layer->layerWH.width	= width;
	layer->layerWH.height	= height;
	layer->name				= name;
	layer->type				= type;
	layer->visible			= visible;
	layer->x				= x;
	layer->y				= y;

	return layer;
}
// Delete the layer malloc on the heap
void CMap::DestroyLayer(SLayer* layer)
{
	// Delete the index data
	delete layer->data;
	layer->data = NULL;

	// Delete the layer
	delete layer;
	layer = NULL;
}

/* Tileset information */
int  CMap::GetTilesetCount()
{
	return m_iTilesetCount;
}
void CMap::SetTilesetCount(int tilesetCount)
{
	m_iTilesetCount = tilesetCount;
}
// Add a new layer, call the build layer method inside
void CMap::AddTileset(std::string image, std::string name, int firstGrid, int imageWidth,
					int imageHeight, int tileWidth, int tileHeight)		
{
	m_pvspTileSet->push_back( this->BuildTileset(image, name, firstGrid, imageWidth, imageHeight, tileWidth, tileHeight) );
}
// Build a layer based on the information passed in
CMap::STileSet* CMap::BuildTileset(std::string image, std::string name, int firstGrid, int imageWidth,
					int imageHeight, int tileWidth, int tileHeight)		
{
	STileSet* tileset			= new STileSet;	// new a layer on heap
	tileset->image				= image;
	tileset->imageWH.width		= imageWidth;
	tileset->imageWH.height		= imageHeight;
	tileset->name				= name;
	tileset->tileWH.width		= tileWidth;
	tileset->tileWH.height		= tileHeight;
	tileset->firstGrid			= firstGrid;

	return tileset;
}
// Delete the layer malloc on the heap
void CMap::DestroyTileset(STileSet* tileset)
{
	// Delete the tileset
	delete tileset;
	tileset = NULL;
}
// ��������������ɿ��ӵĵ�ͼ
// 1���õ��Ĳ�����MapSurface�����Ŀ�ꣻx, yҲ������Ƭ�ڵ�ͼ�ϵ�λ�ã�TileIndex����Ƭ�������������Դ��
// 2��˼·��ͨ��TileIndex�ҵ���Ƭ����������λ�úʹ�С����ͼ�ϵ�x��y�Ѿ��ҵ���Ȼ��ֻ��һ��CopyRect����
//    ����ʵ�ְ�����ľ���copy����ͼ��Surface����ˡ�
bool CMap::BuildMapSurface(int agentPosX, int agentPosY)
{
	// ChangeViewToMapCoord(agentPosX, agentPosY);
	// For simplity, here just use the most simple example: the view's original point
	// Is same to the map's originale point
	int tileIndex = 1;
	for(int i = 0; i < WND_HEIGHT / m_sTileWH.height; ++i)
	{
		for(int j = 0; j <  WND_WIDTH/ m_sTileWH.width; ++j)
		{
			m_pTiles->BuildTileAt(tileIndex, m_ipMapSurface, j * m_sTileWH.width, i * m_sTileWH.height);
		}
	}
	return true;
}
//��������������x, y��������������view��ߵ����꣬Ҫͨ��һ�����ֶ�ת��������ڵ�ͼ������
//void CMap::DrawMap(int agentPosX, int agentPosY)
//{
//	ChangeToMapCoord(agentPosX, agentPosY);		//��������������Ѿ�����Ե�ͼԭ�������
//
//	back:
//	GetViewOrigCoord(viewOrigX, viewOrigY, agentPosX, agentPosY);		//ͨ���������λ�û���ӿڵ�ԭ������
//	tileIndex = GetTileIndexAtCoord(viewOrigX, viewOrigY);//���ĳһ�����µ���Ƭ������
//	m_pTiles->BuildTileAt(tileIndex, m_ipMapSruface, mapX, mapY)//��ͼ�����������������Ƭ����,mapX, mapY��ʼ��Ϊ0��0
//	{
//		//�ڲ�ʵ��Ϊ��
//		tileTexture = CTile::FindTileTextureAt(tileIndex);//ͨ�������ҵ�����
//		tileTexture.GetTileCoordAt(tileIndex, tileTextureX, tileTextureY);//�ڸ��������涨λ��Ƭ��ԭ������
//		CopyRect(tileTexture, tileTextureX, tileTextuerY, tileWidth, tileHeight, 
//			m_ipSureface, mapX, mapY);//��������ָ������ľ��ο�������ͼ������ȥ
//	}
//	viewOrigX += tileW;
//	viewOrigY += tileH;
//	mapX += tileH;
//	mapY += tileH;
//	Repeat and Go back to 'back' label 
//		Until the Whole map is Built fine and nicely~~
//}
void CMap::ChangeViewToMapCoord(int& x, int& y)
{
	// Do nothing until find the way to transform...
}
void CMap::DrawMap(int agentPosX, int agentPosY)
{
	IDirect3DSurface9* 		m_pBackBufferSurface;
	// The Debug trick here is get the description structure of each surface,
	// Then compare the two structure, the two surface can replace each other only when...
	// The information members of the two description be exactlly inditical!
	//IDirect3DSurface9* 		testSurface;
	//D3DSURFACE_DESC			backSurfaceDesc, testSurfaceDesc;

	BuildMapSurface(agentPosX, agentPosY);

	//if(FAILED(m_ipDevice->CreateOffscreenPlainSurface(800, 600,
	//	D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &testSurface, NULL)))
	//	MessageBox(NULL, L"Create test surface error!", L"Error", MB_OK);
	//testSurface->GetDesc(&testSurfaceDesc);

	// Get the main surface of the system
	if(FAILED(m_ipDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBufferSurface)))
		MessageBox(0, L"ERROR", L"Get backbuffer error", MB_OK);
	// Copy the map surface to replace the main surface, the main surface is the same to back buffer surface.
	if(FAILED(m_ipDevice->UpdateSurface(m_ipMapSurface, NULL, m_pBackBufferSurface, NULL)))// if rect==null, point must be 0,0 or null
		MessageBox(0, L"ERROR", L"Swap map surface error", MB_OK);
	//m_pBackBufferSurface->GetDesc(&backSurfaceDesc);

	m_pBackBufferSurface->Release();
	m_pBackBufferSurface = NULL;
}