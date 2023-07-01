#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Processo {
public:
    long long int t;
    int c;

    Processo(){}
};

class Comp {
public:
    bool operator () (const Processo* p1, const Processo* p2) {
        return (p1->c > p2->c);
    }
};

bool sortAlg(Processo* p1, Processo* p2){
    return p1->t < p2->t;
}

int main(int argc, const char * argv[]) {
    int n, i;
    Processo *p, *q;
    long long int espera;
    long long int tempoExec;
    priority_queue<Processo*, vector<Processo*>, Comp> f;
    vector<Processo*> processos;

    while(cin >> n){
        espera = 0;
        tempoExec = 0;
        processos.clear();

        for(i = 0; i < n; i++) {
            p = new Processo();
            cin >> p->t >> p->c;

            if(i == 0 || p->t < tempoExec)
                tempoExec = p->t;

            processos.push_back(p);
        }

        sort(processos.begin(), processos.end(), sortAlg);
        // Execute (1,10) => wait = 0, curTume = 11;
        // Execute (7,5) => wait = 0 + 11-7 = 4, curTime = 11+5 = 16;
        // Execute (6,10) => wait = 4 + 16-6 = 14, curTime = 16+10 = 26;
        // Execute (5,15) => wait = 14 + 26-5 = 35, curTime = 26+15 = 41;
        // So the answer is 35. The time counter starts with 1, not with 0, hence the difference between 32 and 35.
        for(Processo* p : processos){
            if(p->t > tempoExec) {
                q = f.top(); f.pop();
                if(q->t <= tempoExec)
                    espera += tempoExec - q->t;
                else
                    tempoExec = q->t;
                tempoExec += q->c;
            }
            f.push(p);
        }

        while(!f.empty()) {
            q = f.top(); f.pop();
            if(q->t <= tempoExec)
                espera += tempoExec - q->t;
            else
                tempoExec = q->t;
            tempoExec += q->c;
        }

        cout << espera << endl;
    }

    return 0;
}