#include <fstream>
#include <conio.h>
#include <cmath>

namespace CRog
{
	void print(const char* s)
	{
		//char* p = s;
		/*
		while (*s != 0)
		{
			_putch(*s++);
		}
		*/

		for (; *s != 0; s++)
		{
			_putch(*s);
		}
	}

	void printFixedWidth(const char* s, const int width)
	{
		int count = 0;
		for (; (*s != 0) && (count < width); s++)
		{
			_putch(*s);
			count++;
		}
		for (; count < width; count++)
		{
			_putch(' ');
		}
	}

	void read(char* buff, int maxSize)
	{
		const char* const pEnd = buff + maxSize;
		for (char c = _getch(); (c != 13) && (buff < pEnd - 1); c = _getch(), buff++)
		{
			*buff = c;
			_putch(c);
		}
		*buff = 0;
	}

	void strcpy(const char* pSource, char* pTarget, int maxBufferSize)
	{
		int n = 0;
		for (; *pSource!= 0 && (n+1 < maxBufferSize); pSource++,pTarget++,n++)
		{
			*pTarget= *pSource;
		}
		*pTarget = 0;
	}

	int str2int(const char* const ch)
	{
		int len = 0;
		while ((*(ch + len) >= 48) && (*(ch + len) <= 57))
		{
			len++;
		}
		int total = 0;
		for (int i = len - 1; i >= 0; i--)
		{
			total += ( int(pow(10, len - i - 1))) * (*(ch + i) - int(48) );
		}
		return total;

	}

	int str2int2(const char* const ch)
	{
		// set r pointer 
		const char* r = ch;
		for (; *r >= '0' && *r <= '9'; r++);
		r--;
		// convert factored values and accumulate
		int total = 0;
		int factor = 1;
		for (; r >= ch; r--)
		{
			total += (*r - '0') * factor;
			factor *= 10;
		}
		return total;

	}

	void int2str(int n, char* ch)
	{
		int nDigits = 1;
		int factor = 1;
		//for (; n / factor >= 10; nDigits++, factor *= 10);
		while (n / factor >= 10)
		{
			nDigits++;
			factor *= 10;
		}

		int i = 0;
		for (; factor >= 1; factor /= 10, i++)
		{
			int digit = n / factor;
			ch[i] = digit + '0';
			n -= factor * digit;
		}
		ch[i] = 0;
	}

	void int2str2(int n, char* ch)
	{
		int arr[10] = { 0 };
		int nDigits = 0;
		for (; n > 0; nDigits++)
		{
			arr[nDigits] = n % 10;
			n /= 10;
		}
		//char* p = ch;
		for (int i = 0; i < nDigits; i++, ch++)
		{
			*ch = arr[nDigits - i - 1] + '0';
		}
		*ch = 0;
	}

	void strrev(char* pl)
	{
		char* pr = pl;
		for (; *(pr + 1) != 0; pr++);

		for (; pl < pr; pl++, pr--)
		{
			//std::swap(*str, *pr);
			const char temp = *pl;
			*pl = *pr;
			*pr = temp;
		}
	}

	void int2str3(int n, char* buff, int size)
	{

		char* const pStart = buff;
		char* const pEnd = buff + size;
		for (; n > 0 && (buff + 1 < pEnd) ; n /= 10 , buff++)
		{
			*buff = n % 10 + '0';
		}
		*buff = 0;
		strrev(pStart);
	}

	int fib_rec(int n)
	{
		if (n == 0)
		{
			return 0;
		}
		else if (n == 1)
		{
			return 1;
		}
		else
		{
			return fib_rec(n - 2) + fib_rec(n - 1);
		}
	}

	int fib_it(int n)
	{
		int t0 = 0;
		int t1 = 1;
		for (int i = 0; i < n; i++)
		{
			int temp = t1;
			t1 += t0;
			t0 = temp;
		}
		return t0;
	}

	void readNumber(char* ch)
	{
		print("Enter a number: ");
		read(ch, 5);
	}
}

class CData {
private:
	class Entry {
	public:
		Entry() = default;
		Entry(const char* name, const int number)
			:
			n(number)
		{
			CRog::strcpy(name,this->name, sizeof(this->name) );
		}
		void Print() const
		{
			CRog::printFixedWidth(name, 10);
			_putch('  |');
			for (int j = 0; j < n; j++)
			{
				_putch('=');
			}
			_putch('\n');
		}
		void Deserialize(std::ifstream& in)
		{
			in.read(name, sizeof(name));
			in.read(reinterpret_cast<char*>(&n), sizeof(n));
		}
		void Serialize(std::ofstream& out) const
		{
			out.write(name, sizeof(name));
			out.write(reinterpret_cast<const char*>(&n), sizeof(n));
		}
		static constexpr int nameBufferSize = 10;
	private:
		char name[nameBufferSize];
		int n;
	};

public:
	void AddEntry(const char* p_in, const int n_in)
	{
		if (nEntries < maxNumberEntries)
		{
			entries[nEntries++] = { p_in, n_in };
		}
	}
	void RemoveEntry(int n)
	{
		if (n < nEntries && n>=0)
		{
			for (int i = n; i < nEntries-1; i++)
			{
				entries[i] = entries[i + 1];
			}
			nEntries--;
		}
	}
	void GetEntryFromUser()
	{
		CRog::print("Enter name:");
		char buff1[256];
		CRog::read(buff1, sizeof(buff1) );
		CRog::print("\n");
		
		int val = 201;
		while (val > 200)
		{
			CRog::print("Enter value:");
			char buff2[10];
			CRog::read(buff2, 10);
			CRog::print("\n");
			val = CRog::str2int2(buff2);
			if (val > 200)
			{
				CRog::print("Value needs to be smaller than 200.\n");
			}
		}
		AddEntry(buff1,val);

	}
	void Print() const
	{
		CRog::print("\n     Beatiful Chart Bitches!\n");
		CRog::print("     -----------------------\n\n");
		for (int i=0;i<nEntries;i++)
		{
			entries[i].Print();
		}
		
	}
	void Save(const char* fileName)
	{
		std::ofstream out(fileName, std::ios::binary);
		out.write(reinterpret_cast<char*>(&nEntries), sizeof(nEntries));
		for (int i = 0; i < nEntries; i++)
		{
			entries[i].Serialize(out);
		}
	}

	void Load(const char* fileName)
	{
		std::ifstream in(fileName, std::ios::binary);
		if (!in.good())
		{
			CRog::print("\nError: file not found..\n");
		}
		else
		{
			in.read(reinterpret_cast<char*>(&nEntries), sizeof(nEntries));
			for (int i = 0; i<nEntries; i++)
			{
				entries[i].Deserialize(in);
			}
		}
	}

private:
	static constexpr int maxNumberEntries = 50;
	Entry entries[maxNumberEntries];
	int nEntries = 0;
};

void MenuChoice(char& ch)
{
	CRog::print("\n(l)oad (s)ave (a)dd (r)emove (q)uit or (p)rint\n");
	ch='0';
	while (ch != 'l' && ch != 's' && ch != 'a' && ch != 'q' && ch  != 'p' && ch != 'r')
	{
		ch = _getch();
	}
}

int main()
{
	CData dbase;
	
	bool quitting = false;
	char ch='0';
	
	do
	{
		MenuChoice(ch);
		char fileName[25];
		switch (ch)
		{
			case 'p':
				dbase.Print();
				break;
			case 'a':
				dbase.GetEntryFromUser();
				break;
			case 'r':
				CRog::print("\nWhich entry number? ");
				char buff[3];
				CRog::read(buff, 3);
				dbase.RemoveEntry(CRog::str2int2(buff)-1);
				break;					
			case 's':
				CRog::print("\nFilename: ");
				CRog::read(fileName, sizeof(fileName));
				dbase.Save(fileName);
				break;
			case 'l':
				CRog::print("\nFilename: ");
				CRog::read(fileName, sizeof(fileName));
				dbase.Load(fileName);
				break;
			case 'q':
				quitting = true;
		}
	} 
	while (!quitting);
	//while (!_kbhit());
	return 0;
}