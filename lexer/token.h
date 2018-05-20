//
// Created by Pablo Brenes on 25 mar 2018.
//

#ifndef PARSER_TOKEN_H
#define PARSER_TOKEN_H

#include <iostream>

struct token {
    int codigoFamilia;
    std::string lexema;
    int fila;
    int columnaInicio;
    int columnaFin;
    int codigoError;

    token(int _fila, int _columnaInicio);

    void asignarCodigoFamilia(int _codigoFamilia);

    void asignarLexema(std::string _lexema);

    void asignarColumnaFin(int _columnaFin);

    void asignarCodigoError(int _codigoError);

    void aumentarFilaInicio();

    void imprimirToken();

    void ajustarInicioLexema();
};

#endif //PARSER_TOKEN_H
