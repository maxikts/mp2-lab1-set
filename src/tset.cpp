// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"


TSet::TSet(int mp) : BitField(mp)

{ 
	MaxPower = mp;


}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower=s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)

{
	MaxPower = bf.GetLength();

}

TSet::operator TBitField()
{
	TBitField bf(BitField);
	return bf;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{ 
	return MaxPower;

}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
    
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{	
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;

}

int TSet::operator==(const TSet &s) const // сравнение
{
	int res = 0;
	if ((MaxPower == s.MaxPower) && (BitField == s.BitField)) res = 1;
    return res;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	int res = 1;
	if ((MaxPower == s.MaxPower) && (BitField == s.BitField)) res = 0;
	return res;
}

TSet TSet::operator+(const TSet &s) // объединение

{
	if (s.MaxPower > MaxPower) MaxPower = s.MaxPower;
	BitField = BitField | s.BitField;
	return *this;

}

TSet TSet::operator+(const int Elem) // объединение с элементом
{	
	if ((Elem > -1) && (Elem < BitField.GetLength())) {
		TSet res(*this);
		res.BitField.SetBit(Elem);
		return res;
	}
	else throw - 1;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	BitField = BitField & Elem;
	return *this;

}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet temp(BitField&s.BitField);
	return temp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet temp(~BitField);
	return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int temp; char ch;
	do { istr >> ch; } while (ch != '{');
	do {
		istr >> temp; s.InsElem(temp);
		do { istr >> ch; } while ((ch != ',') && (ch != '}'));
	} while (ch != '}');
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int i, n; char ch = ' ';
	ostr << "{";
	n = s.GetMaxPower();
	for (i = 0; i < n; i++) {
		if (s.IsMember(i)) { ostr << ch << ' ' << i; ch = ','; }

	}
	ostr << "}";
	return ostr;

}
