//Date: 2013-10-28 16:42
//Modify:�޸�Sprite����ʾ��Χ������Sprite������ʾ������Ļ����
//		 �޸Ĵ��ڵĸ߶ȣ���ԭ���ĸ߶�������24�����������ͻ����ĸ߶Ⱦ���600��

//Date: 2013-10-31 23:01
//Modify:��������һ��OffsetPlainBuffer�����Ͳ����֡�ˣ����ڽ���˵�֡��
//		������������״�������˲�����ĵط���graphics deviceӦ����ȫ�ֵĻ���
//		������winmain��������װ��һ����

//Date: 2013-11-4  19:40
//Modify:�����ݴ�Graphic�������������һ����������࣬����ฺ��AI���߼������ݵĹ���
//		�����Ͳ���ʹ��Game���Եú��ҡ�

//Date: 2013-11-5 18:11
//Modify:ʵ����С��ģ��״̬�Զ���������������״̬��������״̬ͬʱ��Ӧ�ڲ�ͬ�Ŀ��Ʋ���
//      ������Ҫ�Ż�����Ϊ�еĵط�ʹ����Ȩ��֮�ƣ���Ҫ�����У�1��agent�����ʹ������
//		2��ö�ٷ���ֵ���ͳ������ܱ������⣻3�����������ʹ�����⣬����ķ���ò���ǶԵ�
//		���Ǹо��܆��£����ﲻֱ��ʹ�ú���ָ���أ�(��Ȼ����Ŀ��Ʋ��Զ���member function,�����ú���ָ���)

//Date: 2013-11-13 15:23(������һ�������Ĺ��̺ϲ�����������ʵ��TileMap)
// Four Step:
// 1: Parser the map, read the tile and layer information(DONE!)
// 2: Load sprites need by map(How to load and how to store the texture)
// 3: Rearrange the map information and make a clean surface in the end.
// 4: Swap the surface created to the main surface
// Appendix: make a camera!

// Two way to store the tileset image
// 1: Store in a texture vector
// 2: Store in a plain surface(Try this first!)

//Date: 2013-11-22 17:07Ҫ�ı�һЩ����
//��Ϊ֮ǰagent�������õĶ����������(������ڴ��ڵ�����)�����ڵ�ͼ����ʾ��ʱ��ͻ�not easy��Ŀǰ��
//�뷨���ǰ����е����궼תΪ����ڵ�ͼ������(���ҳ�Ϊ��������)��