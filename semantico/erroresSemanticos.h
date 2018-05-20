//
// Created by Pablo Brenes on 12 may 2018.
//

#ifndef LEXICO_ERRORESSEMANTICOS_H
#define LEXICO_ERRORESSEMANTICOS_H

const char errorIdentificadorDuplicado[] = "Error 301, redifinicion del identificador '%s'. En linea: %d, columna: %d\n";
const char errorIdentificadorNoDeclarado[] = "Error 302, el identificador '%s' no fue declarado en este bloque. En linea: %d, columna: %d\n";
const char  errorElementoNoEsTipoDefinido[] = "Error 303, el identificador '%s' no corresponde a un tipo definido por el usuario. En linea: %d, columna: %d\n";

#endif //LEXICO_ERRORESSEMANTICOS_H
