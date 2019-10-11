// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw - 1;
		BitLen = len;
		MemLen = (BitLen + 31) >> 5;
		pMem = new TELEM[MemLen];
		if (pMem != NULL)
			for (int i = 0; i < MemLen; i++) pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if(pMem!=NULL) for (int i = 0; i < MemLen; i++) { pMem[i] = bf.pMem[i]; }
}

TBitField::~TBitField()
{ 
		delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n > -1) && (n < BitLen)) {
		return n >> 5;
	}
	else throw -1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n > -1) && (n < BitLen)) {
		return 1 << (n & 31);
	}
	else throw - 1;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{ 
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	
	if ((n > -1) && (n < BitLen)) {
	pMem[GetMemIndex(n)] |= GetMemMask(n);}
	else throw - 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >-1) && (n < BitLen))
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else throw - 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) && (n < BitLen)) {
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	}
	else throw - 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (BitLen != bf.BitLen) { res = 0; return res; }
	else if (MemLen != bf.MemLen) { res = 0; return res; }
	else
		for (int i = 0; i < MemLen; i++) { if (pMem[i] != bf.pMem[i]) { res = 0; return res; } }
  return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int res = 1;
	if ((BitLen == bf.BitLen)&& (MemLen == bf.MemLen)) 
		{ for (int i = 0; i < MemLen; i++)
			{ if (pMem[i] == bf.pMem[i])
				{ res = 0; return res; } } }
	
	return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len)len = bf.BitLen;
	TBitField a(len);
	for (int i = 0; i < MemLen; i++)a.pMem[i] = pMem[i];
	for (int i = 0; i < len; i++)a.pMem[i] |= bf.pMem[i];

	return a;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len)len = bf.BitLen;
	TBitField a(len);
	for (int i = 0; i < MemLen; i++)a.pMem[i] = pMem[i];
	for (int i = 0; i < bf.BitLen; i++)a.pMem[i] &= bf.pMem[i];

	return a;
	
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField a(BitLen);
	for (int i = 0; i < MemLen; i++) {
		for (int k = 0; k < BitLen; k++) {
			if (GetBit(k) == 0) a.SetBit(k);
			else a.ClrBit(k);
		}
	}
	return a;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char ch; int i = 0;
	do { istr >> ch; } while (ch != ' ');
	while (1) {
		istr >> ch;
		if (ch == '0') { bf.ClrBit(i++); }
		else if (ch == '1') { bf.SetBit(i++); }
		else break;
	
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++) {
		if (bf.GetBit(i)) { ostr << '1'; }
		else ostr << '1';
	}
	return ostr;
}
