#include <iostream>
#include <time.h>

using namespace std;

class Data
{
private:
	int dia;
	int mes;
	int ano;

public:
	Data(int dia, int mes, int ano)
	{
		this->dia = dia;
		this->mes = mes;
		this->ano = ano;
	}

	Data()
	{
		this->dia = 0;
		this->mes = 0;
		this->ano = 0;
	}

	void setDia(int dia)
	{
		this->dia = dia;
	}

	void setMes(int mes)
	{
		this->mes = mes;
	}

	void setAno(int ano)
	{
		this->ano = ano;
	}

	int getDia()
	{
		return this->dia;
	}

	int getMes()
	{
		return this->mes;
	}

	int getAno()
	{
		return this->ano;
	}

	string getData()
	{
		return to_string(this->dia) + "/" + to_string(this->mes) + "/" + to_string(this->ano);
	}

	Data *dia_seguinte()
	{
		Data *d1;
		int diasNoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		d1 = new Data(this->dia, this->mes, this->ano);

		if (d1->ano % 4 == 0)
		{
			diasNoMes[1]++;
		}

		d1->dia++;
		if (d1->dia > diasNoMes[d1->mes - 1])
		{
			d1->dia = 1;
			d1->mes++;
			if (d1->mes > 12)
			{
				d1->mes = 1;
				d1->ano++;
			}
		}
		return d1;
	}
};

class Contato
{
private:
	string email;
	string nome;
	string telefone;
	Data *dtnasc;

public:
	Contato(string email, string nome, string telefone, Data *dtnasc)
	{
		this->email = email;
		this->nome = nome;
		this->telefone = telefone;
		this->dtnasc = dtnasc;
	}

	Contato()
	{
	}

	// Getters
	string getEmail()
	{
		return this->email;
	}

	string getNome()
	{
		return this->nome;
	}

	string getTelefone()
	{
		return this->telefone;
	}

	string getDtnasc()
	{
		return to_string(this->dtnasc->getDia()) + "/" + to_string(this->dtnasc->getMes()) + "/" + to_string(this->dtnasc->getAno());
	}

	// Setters;
	void setEmail(string email)
	{
		this->email = email;
	}

	void setNome(string nome)
	{
		this->nome = nome;
	}

	void setTelefone(string telefone)
	{
		this->telefone = telefone;
	}

	void setDtnasc(Data *data)
	{
		this->dtnasc = data;
	}

	int idade()
	{
		int idade;

		// pega a data de hoje e guarda em tm
		time_t tempo;
		tempo = time(NULL);
		struct tm tm = *localtime(&tempo);

		idade = tm.tm_year + 1900 - dtnasc->getAno();
		//verificando se o contato já fez aniversário;
		if ((tm.tm_mon + 1) > dtnasc->getMes() ||
				((tm.tm_mon + 1) == dtnasc->getMes() && tm.tm_mday < dtnasc->getDia()))
		{
			idade--;
		}

		return idade;
	}
};

int main(int argc, char **argv)
{
	bool sair = false;
	int tamanho = 5, contador = 0, escolha;
	Contato *contatos[tamanho];

	do
	{
		escolha = 0;
		cout << endl
				 << "escolha uma opção: " << endl;
		cout << "1. Cadastrar novo contato" << endl;
		cout << "2. Visualizar contatos" << endl;
		cout << "3. sair" << endl;

		cin >> escolha;

		if (escolha == 1 && contador < 5)
		{
			contatos[contador] = new Contato();
			string nome, email, telefone;

			Data *dtnsc;
			int dt_dia, dt_mes, dt_ano;

			cout << "Digite o nome do " << (contador + 1) << "º contato: ";
			cin >> nome;

			cout << "Digite o email do " << (contador + 1) << "º contato: ";
			cin >> email;

			cout << "Digite o telefone do " << (contador + 1) << "º contato: ";
			cin >> telefone;

			//pegando os dados para a criação da data de nascimento
			cout << "Digite o dia de nascimento do " << (contador + 1) << "º contato: ";
			cin >> dt_dia;

			cout << "Digite o mes de nascimento do " << (contador + 1) << "º contato: ";
			cin >> dt_mes;

			cout << "Digite o ano de nascimento do " << (contador + 1) << "º contato: ";
			cin >> dt_ano;

			Data *dt_nasc = new Data(dt_dia, dt_mes, dt_ano);

			contatos[contador]->setNome(nome);
			contatos[contador]->setEmail(email);
			contatos[contador]->setTelefone(telefone);
			contatos[contador]->setDtnasc(dt_nasc);

			contador++;
		}
		else if (escolha == 1)
		{
			cout << "A agenda de contatos já está cheia, o número máximo de contatos é 5";
		}
		else if (escolha == 2)
		{
			for (int i = 0; i < contador; ++i)
			{
				if (contatos[i] != NULL)
				{
					cout << endl
							 << "Nome do contato: " << contatos[i]->getNome() << endl;
					cout << "Email do contato: " << contatos[i]->getEmail() << endl;
					cout << "Telefone do contato: " << contatos[i]->getTelefone() << endl;
					cout << "Data de nascimento do contato: " << contatos[i]->getDtnasc() << endl;
					cout << "Idade do contato: " << contatos[i]->idade() << endl;
				}
			}
		}
		else
		{
			sair = true;
		}

	} while (!sair);
}