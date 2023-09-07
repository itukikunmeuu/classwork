#include<iostream>

//�N���X�ƃ|�C���^
//��̍\���̂Ɠ���

class TestClass
{
public:
	TestClass();
	~TestClass();
	void print();
private:
	//�����̓s����A�����o��4Byte�̕ϐ��̂ݎg��
	int num0;		//4
	int num1;		//8
	float fnum0;	//12
	float fnum1;	//16

};
//�R���X�g���N�^
TestClass::TestClass():
	num0(10),
	num1(20),
	fnum0(30.0f),
	fnum1(40.0f)
{
}
//�f�X�g���N�^
TestClass::~TestClass()
{
}
//�����o�[�ϐ��̒l��\������
void TestClass::print()
{
	std::cout << "num1 = " << std::endl;
}

int main()
{
	//�N���X�̓�������ɂǂ̂悤�ɔz�u�����H
	TestClass testClass;
	
	//TestClass�̃f�[�^�T�C�Y�́H
	//sizeof���Z�q���g�p���ăT�C�Y���m�F����
	//�N���X�̏ꍇ���\���̂Ɠ������A�����o�ϐ��݂̂���������ɔz�u�����
	std::cout << "size ="  << sizeof(testClass) << std::endl;

	//�N���X�̃����o�ϐ��ɃA�N�Z�X����
	//�ǂ��Ɖ��Z�q���g�p����
	std::cout << "size = " << sizeof(testClass) << std::endl;
	//�N���X�̃����o�[�֐����Ă�
	testClass.print();

	//�N���X�̃|�C���^
	//�\���̂�int�^�̕ϐ��Ɠ���
	TestClass* pClass = &testClass;
	//�|�C���^���烁���o�[�ϐ��ɃA�N�Z�X����
	//�\���̂Ɠ������A���[���Z�q���g�p����
	std::cout << "fnum0 = " << pClass->fnum1 << std::endl;
	//�����o�֐����Ă�
	//��������A���[���Z�q���ǂ�

	return 0;
}

//C����ł�����A�h���X�A�|�C���^�̗��K
/*
struct StructTest
{
	int num0;
	int num1;
	float fnum0;
	float fnum1;
};

int main()
{
	//�ϐ��錾���s�����Ƃ��A��������̕ϐ���ۑ����邽�߂̗̈悪�m�ۂ����
	//��������̂ǂ��ɔz�u����邩�͂킩��Ȃ�
	//�킩��Ȃ����z��͕K�����Ԃɕ���Ŋm�ۂ����
	//�\���̂͐錾�������Ԃɕ��ׂĊm�ۂ����

	//�ϐ��̐錾�@���������int�̃T�C�Y���̗̈悪�m�ۂ����
	int num = 4; //�S�̂Ƃ���Ɋm�ۂ����

	//�z��̐錾�@int��3�Ï��������@�z��̓�������ɕ���Ŕz�u�����
	int tbl[3] = { 1,2,3 }; //�O�A���̊m��

	//�\���̂̐錾 �\���l�Ƀ����o�[�͍\���̂�錾�������ɕ��ׂ����ԂɃ������m�ۂ����
	StructTest test =
	{
		10,			//num1
		20,			//num2
		30.0f,		//fnum1
		40.0f		//fnum2
	};



	//�\���̂̔z��
	StructTest testTbl[3];

	//�|�C���^�̐錾
	//�|�C���^���A�h���X��ۑ����邽�߂̕ϐ�
	//�f�[�^�^*�|�C���^���@�@�Ƃ������`���Ő錾����
	int* pNum;	//���������Ȃ��ƃ|�C���^�̒��ɂǂ�Ȑ����������Ă��邩�킩��Ȃ�
				//�Ȃ̂Ń|�C���^�����������Ă�������

	//int�^�̕ϐ�num�̃A�h���X���擾����pNum�ɕۑ�������
	pNum = &num;

	//pNum�̒��g(num�̃A�h���X)��\������
	std::cout << pNum << std::endl;

	//�A�h���XpNum�̒��ɓ����Ă��鐔�l��\������
	if (pNum != nullptr)//nullptr�͂ǂ��������Ă��Ȃ��̂�nullptr�o�Ȃ����Ƃ��m�F���Ă��珈������
	{
		*pNum = 10; //�|�C���^���Q�Ƃ����Ƀf�[�^���i�[����
		std::cout << (*pNum) << std::endl; //�|�C���^���Q�Ƃ����̃f�[�^��\������
	}

	//�\���̌y�����K
	//test.num0 = 16;
	//std::cout << test.num0 << std::endl;

	//�\���̂̃|�C���^
	StructTest* pStructTest = &test;
	//StructTest�̕\��
	std::cout << pStructTest << std::endl;
	//pStrcttest���w���������g�̕\��
	//�\���̂Ƀ|�C���^���炻�̃����o�[���Q�Ƃ������ꍇ
	//�h�b�g���Z�q�i.�j�ł͂Ȃ��A���[���Z�q�i-���j���g�p����
	std::cout << pStructTest->fnum0 << std::endl;




	//std::cout << "��������o��" << std::endl;



	return 0;
}*/
