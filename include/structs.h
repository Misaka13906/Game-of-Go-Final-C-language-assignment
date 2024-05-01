#ifndef MY_STRUCTS_H
#define MY_STRUCTS_H

typedef struct {
	Color color;
	int x, y, id; // ���꼰id
	int root; // �����Ӳ��鼯�����ϵ����ȵ�id
	int liberty;
		// ��Ϊ����(.root=.id)����洢����id����ʶ���崮����������
		// �������ȣ���������
	bool exist; // ��ʶ�������Ƿ���������
} Move;

typedef struct {
	Color board[Size][Size]; // �����λ�õ�״̬�����ӡ����ӡ��գ�
	int pieces[Size][Size];  // �����λ���ϵ�ǰ���һ�����ӵ�id������Ϊ0
	Move lastMove;  // ���浱ǰ���һ�����ӵ���Ϣ
	int deadBlack;
	int deadWhite;
} Situ;

typedef struct {
	char id;
	int px, py;
	int x1, y1, x2, y2;  // ��ť���ϽǺ����½ǵ�����
	//wchar_t* s;  // text content
	bool disabled;
}Btn;

#endif