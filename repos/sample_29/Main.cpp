#include<iostream>

//クラスとポインタ
//大体構造体と同じ

class TestClass
{
public:
	TestClass();
	~TestClass();
	void print();
private:
	//説明の都合上、メンバは4Byteの変数のみ使う
	int num0;		//4
	int num1;		//8
	float fnum0;	//12
	float fnum1;	//16

};
//コンストラクタ
TestClass::TestClass():
	num0(10),
	num1(20),
	fnum0(30.0f),
	fnum1(40.0f)
{
}
//デストラクタ
TestClass::~TestClass()
{
}
//メンバー変数の値を表示する
void TestClass::print()
{
	std::cout << "num1 = " << std::endl;
}

int main()
{
	//クラスはメモリ上にどのように配置される？
	TestClass testClass;
	
	//TestClassのデータサイズは？
	//sizeof演算子を使用してサイズを確認する
	//クラスの場合も構造体と同じく、メンバ変数のみがメモリ上に配置される
	std::cout << "size ="  << sizeof(testClass) << std::endl;

	//クラスのメンバ変数にアクセスする
	//どっと演算子を使用する
	std::cout << "size = " << sizeof(testClass) << std::endl;
	//クラスのメンバー関数を呼ぶ
	testClass.print();

	//クラスのポインタ
	//構造体やint型の変数と同じ
	TestClass* pClass = &testClass;
	//ポインタからメンバー変数にアクセスする
	//構造体と同じくアロー演算子を使用する
	std::cout << "fnum0 = " << pClass->fnum1 << std::endl;
	//メンバ関数を呼ぶ
	//こちらもアロー演算子も読む

	return 0;
}

//C言語でやったアドレス、ポインタの練習
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
	//変数宣言を行ったとき、メモリ上の変数を保存するための領域が確保される
	//メモリ上のどこに配置されるかはわからない
	//わからないが配列は必ず順番に並んで確保される
	//構造体は宣言した順番に並べて確保される

	//変数の宣言　メモリ上にintのサイズ分の領域が確保される
	int num = 4; //４のところに確保される

	//配列の宣言　intが3津準備される　配列はメモリ上に並んで配置される
	int tbl[3] = { 1,2,3 }; //三つ連続の確保

	//構造体の宣言 構造値にメンバーは構造体を宣言した時に並べた順番にメモリ確保される
	StructTest test =
	{
		10,			//num1
		20,			//num2
		30.0f,		//fnum1
		40.0f		//fnum2
	};



	//構造体の配列
	StructTest testTbl[3];

	//ポインタの宣言
	//ポインタ→アドレスを保存するための変数
	//データ型*ポインタ名　　といった形式で宣言する
	int* pNum;	//初期化しないとポインタの中にどんな数字が入っているかわからない
				//なのでポインタも初期化しておきたい

	//int型の変数numのアドレスを取得してpNumに保存したい
	pNum = &num;

	//pNumの中身(numのアドレス)を表示する
	std::cout << pNum << std::endl;

	//アドレスpNumの中に入っている数値を表示する
	if (pNum != nullptr)//nullptrはどこもさしていないのでnullptr出ないことを確認してから処理する
	{
		*pNum = 10; //ポインタが参照する先にデータを格納する
		std::cout << (*pNum) << std::endl; //ポインタが参照する先のデータを表示する
	}

	//構造体軽く復習
	//test.num0 = 16;
	//std::cout << test.num0 << std::endl;

	//構造体のポインタ
	StructTest* pStructTest = &test;
	//StructTestの表示
	std::cout << pStructTest << std::endl;
	//pStrcttestが指し示す中身の表示
	//構造体にポインタからそのメンバーを参照したい場合
	//ドット演算子（.）ではなくアロー演算子（-＞）を使用する
	std::cout << pStructTest->fnum0 << std::endl;




	//std::cout << "文字列を出力" << std::endl;



	return 0;
}*/
