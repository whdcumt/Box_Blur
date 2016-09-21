#include "stdafx.h"
#include "malloc.h"

/// <summary>
/// ʵ�ֹ��ܣ�	���ܱߵ�ƽ�������浱ǰֵ,����汾
/// <param name="Src">��Ҫ��ֵģ�����������ڴ�ĵ�ַ��</param>
/// <param name="Dest">�����ֵģ����Ľ����</param>
/// <param name="Width">���ݵĿ�ȡ�</param>
/// <param name="Height">���ݵĸ߶ȡ�</param>
/// <param name="Radius">���ڼ���ƽ��ֵ�ľ��ΰ뾶��</param>

void  BoxBlur(float* Src, float *Dest, int Width, int Height, int Radius)
{
	int X, Y, Z, MoveIn, MovOut  ;
	float Sum, InvertAmount = 1.0 / (( 2 * Radius + 1) * (2 * Radius + 1));
	float *Temp = (float *)malloc(Height * Width * sizeof(float));
	float *LinePS, *LinePD;

	//	BoxBlur��һ�����п��Է������Ĺ��̣�����Ƚ����з����BoxBlur��
	//	�õ��м�����Ȼ���ٶ��м��������з����BoxBlur������Եõ����ս����
	
	for (Y = 0; Y < Height; Y++)			//	��ÿ�е����ݽ���BoxBlur��ע������������з����޹صģ���ÿ�еĽ����������໥Ӱ�죬��˺��ʺ��ڲ��л�
	{
		LinePS = Src + Y * Width;			//	��λ����Y�е�һ�����ص��ڴ��ַ
		LinePD = Temp + Y * Width;
		Sum = (Radius + 1) * LinePS[0];		//	�����е�һ�������������� Radius��Χ�ڵ��ۼ�ֵ��������Ե���ñ�Եֵ����, ע������ļ�1��Ϊ�˺����ı��뷽�㣬����ϸ��ζ���+1�������෴��	
		for (Z = 0; Z < Radius; Z++)		// 	����˵�����ѭ���ڲ���Ҫ�����ж�Z�Ƿ���ڵ��ڿ�ȣ��������ַ��ʷǷ��ڴ�Ĵ��󣬵����������ֻ��Radius>Widthʱ���֣������û������ġ�
			Sum += LinePS[Z];				//	�����һ�����Ҳ�������ۼ�ֵ
		for (X = 0; X < Width;X++)			
		{	
			MovOut = X - Radius - 1;						//	������Ƴ�ȥ���Ǹ����ص�����
			if (MovOut < 0) MovOut = 0;						//	�ñ�Եֵ����
			MoveIn = X + Radius;							//	���Ҳ�������Ǹ����ص�����
			if(MoveIn >= Width) MoveIn = Width - 1;			//	�ñ�Եֵ����
			Sum = Sum - LinePS[MovOut] + LinePS[MoveIn];	//	�µ��ۼ�ֵ = �ɵ��ۼ�ֵ - �Ƴ���ֵ + �����ֵ
			LinePD[X] = Sum;								//	���浽��ʱ�ڴ���
		}
	}

	for (X = 0; X < Width; X++)				//	����������ʱ���ݽ����з����BoxBlur���õ����ս�������뷽ʽ��ʵһ���ģ�ֻ���и���Ϊ��
	{
		LinePS = Temp + X;					//	��λ����X�еĵ�һ�����ص��ڴ��ַ
		LinePD = Dest + X;
		Sum = (Radius + 1) * LinePS[0];		//	������ͬ���ĵ�������ע����
		for (Z = 0; Z < Radius; Z++)
			Sum += LinePS[Z * Width];
		for (Y = 0; Y < Height; Y++)
		{	
			MovOut = Y - Radius - 1;
			if (MovOut < 0) MovOut = 0;
			MoveIn = Y + Radius;
			if(MoveIn >= Height) MoveIn = Height - 1;
			Sum = Sum - LinePS[MovOut * Width] + LinePS[MoveIn * Width];			//	ע�������*Width��
			LinePD[Y * Width] = Sum * InvertAmount;					//	��ƽ��ֵ������ĳ˷�Ҫ�ȳ�������ˣ�����Ϊʲô���ó˷��ء�
		}
	}
	free(Temp);			//	ע���ͷ��ڴ�
}