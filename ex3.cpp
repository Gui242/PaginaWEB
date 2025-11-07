#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <unistd.h> // para sleep()
using namespace std;

// Função para limpar o ecrã no Linux
void limparEcrã() {
    system("clear");
}

// Mostra o tabuleiro
void mostrarTabuleiro(int j1, int j2, int j3, int j4, int numJogadores, int CASAS) {
    cout << "======= JOGO DA GLORIA =======\n";
    for (int i = 1; i <= CASAS; i++) {
        bool ocupado = false;

        if (i == j1) { cout << setw(4) << "J1"; ocupado = true; }
        else if (i == j2 && numJogadores >= 2) { cout << setw(4) << "J2"; ocupado = true; }
        else if (i == j3 && numJogadores >= 3) { cout << setw(4) << "J3"; ocupado = true; }
        else if (i == j4 && numJogadores >= 4) { cout << setw(4) << "J4"; ocupado = true; }

        if (!ocupado) cout << setw(4) << i;
        if (i % 10 == 0) cout << endl;
    }
    cout << "==============================\n";
}

int main() {
    srand(time(0));
    const int CASAS = 30;

    int numJogadores;
    bool contraCPU = false;

    cout << " === JOGO DA GLORIA ===\n";
    cout << " Chega à casa 30 para vencer!\n";
    cout << " Existem 5 casas especiais!\n\n";

    cout << " Quantos jogadores (1 a 4)? ";
    cin >> numJogadores;

    if (numJogadores < 1) numJogadores = 1;
    if (numJogadores > 4) numJogadores = 4;

    // Se for só 1 jogador, ativa CPU
    if (numJogadores == 1) {
        contraCPU = true;
        numJogadores = 2; // jogador + CPU
    } else if (numJogadores >= 2) {
        cout << " Desejas que o último jogador seja o computador? (1 = Sim, 0 = Nao): ";
        cin >> contraCPU;
    }

    cin.ignore(10000, '\n'); // limpa o buffer

    int j1 = 0, j2 = 0, j3 = 0, j4 = 0;
    bool perdeTurno1 = false, perdeTurno2 = false, perdeTurno3 = false, perdeTurno4 = false;
    int turno = 1;

    while (true) {
        limparEcrã();
        mostrarTabuleiro(j1, j2, j3, j4, numJogadores, CASAS);

        cout << "\n--- Turno do Jogador " << turno << " ---\n";

        // verificar se o jogador perde a vez
        bool perdeTurno = false;
        if (turno == 1 && perdeTurno1) { perdeTurno = true; perdeTurno1 = false; }
        else if (turno == 2 && perdeTurno2) { perdeTurno = true; perdeTurno2 = false; }
        else if (turno == 3 && perdeTurno3) { perdeTurno = true; perdeTurno3 = false; }
        else if (turno == 4 && perdeTurno4) { perdeTurno = true; perdeTurno4 = false; }

        if (perdeTurno) {
            cout << "    Jogador " << turno << " perde esta rodada!\n";
            sleep(2);
            turno++;
            if (turno > numJogadores) turno = 1;
            continue;
        }

        // CPU joga automaticamente
        if (contraCPU && turno == numJogadores) {
            cout << " O computador vai lançar o dado...\n";
            sleep(1);
        } else {
            cout << " Pressiona ENTER para lançar o dado...";
            cin.ignore(10000, '\n');
        }

        int dado = rand() % 6 + 1;
        cout << " Saiu o número: " << dado;

        int *pos;
        bool *penaliza;

        if (turno == 1) { pos = &j1; penaliza = &perdeTurno1; }
        else if (turno == 2) { pos = &j2; penaliza = &perdeTurno2; }
        else if (turno == 3) { pos = &j3; penaliza = &perdeTurno3; }
        else { pos = &j4; penaliza = &perdeTurno4; }

        *pos += dado;

        // Casas especiais
        if (*pos == 5)  { cout << " Casa 5: Avanças para a casa 10!\n"; *pos = 10; }
        if (*pos == 12) { cout << " Casa 12: Descansas aqui e perdes a próxima rodada!\n"; *penaliza = true; }
        if (*pos == 20) { cout << " Casa 20: Retrocedes para a casa 14!\n"; *pos = 14; }
        if (*pos == 22) { cout << " Casa 22: Avanças para a casa 27!\n"; *pos = 27; }
        if (*pos == 28) { cout << " Casa 28: Armadilha! Voltas para a casa 24!\n"; *pos = 24; }

        // Vitória
        if (*pos >= CASAS) {
            limparEcrã();
            cout << "\n 🎉 Jogador " << turno << " chegou à casa 30 e venceu o jogo! 🎉\n\n";
            mostrarTabuleiro(j1, j2, j3, j4, numJogadores, CASAS);
            break;
        }

        cout << "\nPosições:\n";
        cout << " Jogador 1 -> casa " << j1 << endl;
        if (numJogadores >= 2) cout << " Jogador 2 -> casa " << j2 << endl;
        if (numJogadores >= 3) cout << " Jogador 3 -> casa " << j3 << endl;
        if (numJogadores >= 4) cout << " Jogador 4 -> casa " << j4 << endl;

        // Próximo turno
        turno++;
        if (turno > numJogadores) turno = 1;

        sleep(1);
    }

    return 0;
}
