//
// Created by Pablo Brenes on 25 mar 2018.
//

#include "token.h"
#include <utility>

using namespace std;

token::token(int _fila, int _columnaInicio) {
    codigoFamilia = -1;
    lexema = "";
    fila = _fila;
    columnaInicio = _columnaInicio;
    columnaFin = -1;
    codigoError = 0;
}

void token::asignarCodigoFamilia(int _codigoFamilia) {
    codigoFamilia = _codigoFamilia;
}

void token::asignarLexema(string _lexema) {
    lexema = std::move(_lexema);
}

void token::asignarColumnaFin(int _columnaFin) {
    columnaFin = columnaInicio + _columnaFin;
}

void token::asignarCodigoError(int _codigoError) {
    codigoError = _codigoError;
}

void token::aumentarFilaInicio() {
    fila++;
    columnaInicio = 1;
}

void token::imprimirToken() {
    cout << "Token:" << endl;
    cout << '\t' << "Codigo familia: " << codigoFamilia << endl;
    cout << '\t' << "Lexema: " << lexema << endl;
    cout << '\t' << "Ubicacion: " << fila << ":" << columnaInicio << "," << columnaFin << endl;
    cout << '\t' << "Codigo de error: " << codigoError << endl;
    //cout << "Codigo familia: " << codigoFamilia << " " << "Lexema: " << lexema << endl;
}

void token::ajustarInicioLexema() {
    while (lexema.front() == ' ' or lexema.front() == '\t') {
        lexema.erase(0, 1);
        columnaInicio++;
    }
}