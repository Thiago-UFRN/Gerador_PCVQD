#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <ctime>
#include <chrono>
#include <random>
#include<algorithm>
#include<cmath>

using namespace std;

#define all(v) v.begin(), v.end()
#define contains(c,x) (find(all(c),x) != (c).end())

double randDouble(double begin, double end) {
	unsigned seed = static_cast<int> (chrono::system_clock::now().time_since_epoch().count());
	default_random_engine generator(seed);
	uniform_real_distribution<double> distribution(begin, end);
	return distribution(generator);
}

int randInt(int begin, int end) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  	std::default_random_engine generator (seed);
	std::uniform_int_distribution<int> distribution(begin,end);
    return distribution(generator) ;
}

class ConjuntoDisj {
private:
    ConjuntoDisj* parent;
    int rank;
    int _value;

    ConjuntoDisj(int _value) {
        this->_value = _value;
        this->parent = this;
        this->rank = 0;
    }

public:

    ConjuntoDisj() {
        this->rank = 0;
    }

    //Faz o make set de valor
    static ConjuntoDisj* makeSet(int _value) {
        ConjuntoDisj* retorno = new ConjuntoDisj(_value);
        return retorno;
    }

    int value() {
        return this->_value;
    }

    //Procura o representante e compara 
    ConjuntoDisj* Find() {
        ConjuntoDisj* current = this;
        ConjuntoDisj* last = this;
        while (current->parent != current) {
            last->parent = current->parent;
            last = current;
            current = current->parent;
        }
        return current;
    }

    //Faz uniao de dois conjuntos disjuntos
    ConjuntoDisj* Union(ConjuntoDisj* other) {
        ConjuntoDisj* root1 = other->Find();
        ConjuntoDisj* root2 = this->Find();
        if (root1->rank < root2->rank) {
            root1->parent = root2;
            return root2;
        } else if (root1->rank > root2->rank) {
            root2->parent = root1;
            return root1;
        } else {
            root2->parent = root1;
            root1->rank++;
            return root1;
        }
    }

    //Verifica se dois conjuntos tem o mesmo representante
    static bool areUnited(ConjuntoDisj* union1, ConjuntoDisj* union2) {
        return union1->Find() == union2->Find();
    }
};

class Aresta {
public:
    int id, v1, v2;
    double peso;

    Aresta() {
        id = 0; v1 = 0; v2 = 0; peso = 0.0;
    }

    Aresta(int v1, int v2, double peso, int id) : v1(v1), v2(v2), peso(peso), id(id) { }

    bool operator<(const Aresta &e) const {
        return this->peso < e.peso;
    }
    
    bool operator==(const Aresta &e) const {
        return (id == e.id && v1 == e.v1 && v2 == e.v2 && peso == e.peso);
    }
};

double spanningTree(vector<Aresta> &grafo, int n) {
	vector<Aresta> arvore;

	sort(grafo.begin(), grafo.end());

	ConjuntoDisj* conjDisj[n];
    
    for(int i = 0; i < n; i++) {
        conjDisj[i] = ConjuntoDisj::makeSet(i);
    }

	int a = 0;
	while(arvore.size() < (n-1)) {
        Aresta aresta = grafo[a];
        
        if(!contains(arvore, aresta)) {
            if(!ConjuntoDisj::areUnited(conjDisj[grafo[a].v1], conjDisj[grafo[a].v2])) {
                conjDisj[grafo[a].v1]->Union(conjDisj[grafo[a].v2]);
				arvore.push_back(aresta);
            }
        }
		a++;
    }

	double soma = 0.0;

	for(int i = 0; i < n-1; i++) {
		soma += arvore[i].peso;
	}

	return soma;
}

class Passageiro {
public:
	int o, d;
	double tempo, tarifa;
	Passageiro() {}
	Passageiro(int o, int d, double tempo, double tarifa) {
		this->o = o;
		this->d = d;
		this->tempo = tempo;
		this->tarifa = tarifa;
	}
};

int main(int argc, char *argv[]) {
	if(argc != 8) {
		cout << "Poucos/Muitos parâmetros, deveria ser: <n> <max> <min> <capacidade_carro> <max_passageiro> <alpha> <tipo>." << endl;
		return 0;
	}
	
	int n = atoi(argv[1]); // 10
	
	double max = atof(argv[2]); // 250.0
	double min = atof(argv[3]); //100.0
	
	int capacidade_carro = atoi(argv[4]); // 3
	int max_passageiro = atoi(argv[5]); // 2

	double alpha = atof(argv[6]); // 0.0
	
	int tipo = atoi(argv[7]); // 0 - assimetrica; 1 - simetrica
	
	double custo[n][n];
	double tempo[n][n];
	
	double beta = (1.0/2.0)*(1.0-alpha);
	double gamma = 0.0;
	
	if(alpha >= 0) {
		gamma = beta;
	} else {
		gamma = 1.0-beta;
	}
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			custo[i][j] = randDouble(0,1);
		}
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			tempo[i][j] = alpha*custo[i][j]+beta+gamma*randDouble(-1.0,1.0);
			custo[i][j] = custo[i][j] * (max - min) + min;
			tempo[i][j] = tempo[i][j] * (max - min) + min;
			custo[i][j] = floor(custo[i][j]);
			tempo[i][j] = floor(tempo[i][j]);
			if(i == j) {
				custo[i][j] = 0.0;
				tempo[i][j] = 0.0;
			}
		}
	}
	
	if(tipo == 1) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				tempo[j][i] = tempo[i][j];
				custo[j][i] = custo[i][j];
			}
		}
	}

	vector<Aresta> grafo_custo;
	vector<Aresta> grafo_tempo;

	int id = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i != j) {
				grafo_custo.push_back(Aresta(i, j, custo[i][j], id));
				grafo_tempo.push_back(Aresta(i, j, tempo[i][j], id));
				id++;
			}
		}
	}

	double arvore_custo = spanningTree(grafo_custo, n);
	double arvore_tempo = spanningTree(grafo_tempo, n);

	vector<int> vertices_selecionados;
	for(int i = 0; i < n; i++) {
		vertices_selecionados.push_back(i);
	}

	for(int i = 0; i < n/2; i++) {
		int aleatorio = randInt(0, vertices_selecionados.size()-1);
		vertices_selecionados.erase(vertices_selecionados.begin() + aleatorio);
	}

	vector<Passageiro> passageiros;

	for(int i = 0; i < n/2; i++) {
		int quantidade = randInt(1, max_passageiro * capacidade_carro);
		for(int j = 0; j < quantidade; j++) {
			int origem = vertices_selecionados[i];
			int destino = origem;
			do {
				destino = vertices_selecionados[randInt(0, vertices_selecionados.size()-1)];
			} while(origem == destino);
			double tarifa = arvore_custo * randDouble(0.25,0.5);
			double tempo_maximo = arvore_tempo * randDouble(0.25,0.5);
			tarifa = floor(tarifa);
			tempo_maximo = floor(tempo_maximo);
			passageiros.push_back(Passageiro(origem, destino, tempo_maximo, tarifa));
		}
	}

	vector<double> bonus;
	for(int i = 0; i < n; i++) {
		bonus.push_back(randDouble(max,max*4));
		bonus[i] = floor(bonus[i]);
	}

	double quota = 0.0;

	for(int i = 0; i < n; i++) {
		quota += bonus[i];
	}

	quota = quota / 2;
	quota = floor(quota);

	vector<double> delay;
	for(int i = 0; i < n; i++) {
		delay.push_back(randDouble(20,50));
		delay[i] = floor(delay[i]);
	}

	cout << n << " " << passageiros.size() << " " << capacidade_carro << endl << endl;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << custo[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cout << tempo[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

	for(int i = 0; i < passageiros.size(); i++) {
		cout << passageiros[i].tarifa << " " << passageiros[i].o << " " << passageiros[i].d << " " << passageiros[i].tempo << endl;
	}

	cout << endl;

	cout << quota << endl << endl;

	bonus[0] = 0.0;
	delay[0] = 0.0;

	for(int i = 0; i < n; i++) {
		cout << i << " " << bonus[i] << " " << delay[i] << endl;
	}

	return 0;
}
