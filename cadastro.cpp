#include <algorithm>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>



using namespace std;

enum modoDoPrograma
{
    MENUINICIAL=0,
    LISTAGEM=1,
    CADASTRO=2,
    SAIR=3
};

bool convertToBool(string valorBool)
{
    if(valorBool.compare("1")==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

class Produto
{
    private:
    
        string nomeDoProduto;
        string descricaoDoProduto;
        int precoDoProduto;
        bool vendaDisponivel;
    
    public:
        
        Produto(){}
        
        Produto(string nome, string descricao, int preco, bool disponivel)
        {
            nomeDoProduto = nome;
            descricaoDoProduto = descricao;
            precoDoProduto = preco;
            vendaDisponivel = disponivel;
        }

        string getNomeDoProduto()
        {
            return nomeDoProduto;
        }

        string getDescricaoDoProduto()
        {
            return descricaoDoProduto;
        }

        int getPrecoDoProduto()
        {
            return precoDoProduto;
        }

        bool getVendaDisponivel()
        {
            return vendaDisponivel;
        }

        void setNomeDoProduto(string novoNome)
        {
            nomeDoProduto= novoNome;
        }

        void setDescricaoDoProduto(string novaDescricao)
        {
            descricaoDoProduto = novaDescricao;
        }

        void setPrecoDoProduto(int novoPreco)
        {
            precoDoProduto = novoPreco;
        }

        void setVendaDisponivel(bool novoEstado)
        {
            vendaDisponivel = novoEstado;
        }

        bool operator< (const Produto &outroProduto) const{
            return precoDoProduto <outroProduto.precoDoProduto;
        }

};


void leiaProduto(fstream& arquivo,vector<Produto>&listagem)
{
    Produto novoProduto;
    stringstream convertePreco(std::ios_base::app|std::ios_base::in|std::ios_base::out);
    string valor;
    int preco;
    while(!arquivo.eof())
    {
        getline(arquivo,valor);
        novoProduto.setNomeDoProduto(valor);
        
        getline(arquivo,valor);
        novoProduto.setDescricaoDoProduto(valor);
        
        getline(arquivo,valor);
        convertePreco<<valor;
        convertePreco>>preco;
        novoProduto.setPrecoDoProduto(preco);
        
        getline(arquivo,valor);
        novoProduto.setVendaDisponivel(convertToBool(valor));
        
        listagem.push_back(novoProduto);
    }
}


void listeProduto(vector<Produto> listagem)
{
    int i;
    cout<<"|A LISTA\n";
    cout<<"|Nome:preco\n";
    for(i=0;i<listagem.size();i++)
    {
        
        cout<<"|"<<listagem[i].getNomeDoProduto()<<": R$"<<listagem[i].getPrecoDoProduto()/100.0<<"\n";
    }
}

Produto cadastreProduto()
{
    string nome;
    string descricao;
    float preco;
    int  precoProduto;
    char estahDisponivel;
    bool status;

    cout<<"Nome do produto a ser cadastrado\n";
    getline(cin>>ws,nome);
    system("cls");

    cout<<"descricao breve do produto\n";
    getline(cin >> ws,descricao);
    system("cls");

    cout<<"Preco do produto\n";
    cin>>preco;
    preco*=100;
    precoProduto = static_cast<int>(preco);


    system("cls");
    
    
    while(true){
        cout<<"Status do novo produto\n";
        cout<<"Se disponivel, aperte s. Senao, aperte n\n";
    
        cin>>estahDisponivel;
        if(estahDisponivel=='s')
        {
            status = true;
            break;
        }

        else if(estahDisponivel=='n')
        {
            status = false;
            break;
        }
        else
        {
            cout<<"erro\n";
            system("cls");
        }
        
    }
    system("cls");

    return Produto(nome, descricao,precoProduto,status);

}

int main()
{

    modoDoPrograma estadoDoPrograma=MENUINICIAL;
    int modo;
    fstream arquivo;
    arquivo.open("listagem.txt",ios::in|ios::out|ios::app);
    vector<Produto>listagem;
    /*if(arquivo)
    {
        leiaProduto(arquivo,listagem);
    }*/

    
    while(estadoDoPrograma!=SAIR)
       
        switch(estadoDoPrograma)
        {
            case MENUINICIAL:
            {
                cout<<"BEMVINDO AO PROGRAMA DE PRODUTOS\n";
                cout<<"[1] - LISTAR\n";
                cout<<"[2] - CADASTRAR\n";
                cout<<"[3] - SAIR\n";
                cin>>modo;
                estadoDoPrograma=static_cast<modoDoPrograma>(modo);
                
                if(estadoDoPrograma>3)
                {
                    estadoDoPrograma==MENUINICIAL;
                }
                system("cls");
                break;
            }

            case LISTAGEM:
            {
                
                listeProduto(listagem);
                cout<<"[0]-Ordene por preco  [1]-cadastra produto [2]-retorna\n";
                cin>>modo;
                switch(modo)
                {
                    case 0:
                    {
                        std::sort(listagem.begin(),listagem.end());
                        break;
                    }
                    case 1:
                    {
                        modo+=1;
                        estadoDoPrograma=static_cast<modoDoPrograma>(modo);
                        break;
                    }
                    case 2:
                    {
                        estadoDoPrograma=MENUINICIAL;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                system("cls");
                break;
            }

            case CADASTRO:
            {
                listagem.push_back(cadastreProduto());
                arquivo<<listagem.back().getNomeDoProduto()<<"\n";
                arquivo<<listagem.back().getDescricaoDoProduto()<<"\n";
                arquivo<<listagem.back().getPrecoDoProduto()<<"\n";
                arquivo<<listagem.back().getVendaDisponivel()<<"\n";
                
                cout<<"[0]-Cadastrar mais um produto [1]- Listar [2]- Retornar";
                cin>>modo;

                switch(modo)
                {
                    case 0:
                    {
                        break;
                    }
                    case 1:
                    {
                        estadoDoPrograma=LISTAGEM;
                        break;
                    }
                    case 2:
                    {
                        estadoDoPrograma=MENUINICIAL;
                    }
                }
                system("cls");
                
                break;
            }
            case SAIR:
            {
                
                break;
            }
            default:
            {
                estadoDoPrograma = MENUINICIAL;
            }
        }

    return 0;

}