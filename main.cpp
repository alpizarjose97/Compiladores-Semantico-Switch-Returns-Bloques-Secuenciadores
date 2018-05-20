
#include <stack>
#include "lexer/lexer.h"
#include "gramaticas/Gramatica.h"
#include "gramaticas/GTablaFollows.h"
#include "gramaticas/nombresTerminales.h"
#include "semantico/erroresSemanticos.h"

using namespace std;

bool esFollow(int i, int j);

const int posicionNombreArchivo = 1;
bool banderaErrorSintactico = false;
bool banderaErrorSemantico = false;


int main(int argc, char *argv[]) {

    iniciarScanner(argv[posicionNombreArchivo]);

    token *TA = demePrimerToken();
    token *TF ; // Token para guardar ID de funcion
    stack<int> PilaParsing;
    stack<int> PilaAuxiliar;
    stack<bool> PilaNakhaan;
    PilaParsing.push(NO_TERMINAL_INICIAL);

    bool hayRet = false;
    bool usandoFuncion = false;
    bool usandoProc = false;
    bool secuenciadores = false;
    int EAP = 0;
    int regla = 0;


    while (TA->codigoFamilia != MARCA_DERECHA) {
        EAP = PilaParsing.top();
        PilaParsing.pop();
        if (TERMINAL(EAP)) {
            if (EAP == TA->codigoFamilia) {
                TA = demeToken();
            } else {
                banderaErrorSintactico = true;
                cout << "Error: Se esperaba un: '" << strTerminales[EAP] << "' y obtuve un: " << TA->lexema
                     << " en linea: " << TA->fila << " columnaInicio: " << TA->columnaInicio << " columnaFin: "
                     << TA->columnaFin << '\n';
                int bandera = 1;
                do {
                    PilaAuxiliar.push(10);
                    PilaAuxiliar.push(38);
                    PilaAuxiliar.push(39);
                    PilaAuxiliar.push(40);
                    PilaAuxiliar.push(41);
                    PilaAuxiliar.push(42);
                    PilaAuxiliar.push(43);
                    PilaAuxiliar.push(156);

                    do {
                        if (EAP == TA->codigoFamilia) {
                            bandera = 0;
                        } else {
                            EAP = PilaAuxiliar.top();
                            PilaAuxiliar.pop();
                        }

                    } while (!PilaAuxiliar.empty() && bandera);
                    PilaAuxiliar.push(10);
                    PilaAuxiliar.push(156);
                    if (bandera) { TA = demeToken(); }

                } while (TA->codigoFamilia != MARCA_DERECHA && bandera);
            }

        } else if (NO_TERMINAL(EAP)) {
            regla = TablaParsing[EAP - NO_TERMINAL_INICIAL][TA->codigoFamilia];
            if (regla < 0) {
                banderaErrorSintactico = true;
                cout << "Error gramatical " << regla << '\t';
                cout << " en linea: " << TA->fila << " columnaInicio: " << TA->columnaInicio << " columnaFin: "
                     << TA->columnaFin << '\n';
                //int follow = 0;
                int i = MAX_FOLLOWS;
                while (i--) {
                    TA = demeToken();
                    if (esFollow(EAP - NO_TERMINAL_INICIAL, TA->codigoFamilia)) {
                        //follow = 1;
                        break;
                    }
                }
            } else {
                int i = 0;
                while ((LadosDerechos[regla][i] > -1) && (i < MAX_LADO_DER)) {
                    PilaParsing.push(LadosDerechos[regla][i++]);
                }
            }

        } else { //simbolo semantico
            switch (EAP) {

                // Casos de análsis del default en switch
                case RevisarDefault :
                {
                    if (TA->codigoFamilia == 18){
                        int X = PilaNakhaan.top();
                        PilaNakhaan.pop();
                        if(X)
                            cout << "Más de un default en switch "
                                 << " en linea: " << TA->fila << " columnaInicio: " << TA->columnaInicio << " columnaFin: "
                                 << TA->columnaFin << '\n';
                        else
                            PilaNakhaan.push(true);
                        break;
                    }
                    break;
                }
                case EmpujarFalsoNakhaan :
                {
                    if (TA->codigoFamilia == 17) {
                        PilaNakhaan.push(false);
                    }
                    break;
                }
                case BotePilaNakhaan :
                {
                    if (TA->codigoFamilia == 12)
                        PilaNakhaan.pop();
                    break;
                }

                // Casos de análisis de un sólo return por rutina
                case InicializarVariableReturn :
                {
                    if (TA->codigoFamilia == 34) {
                        hayRet = false;
                        usandoFuncion = true;
                    }
                    break;
                }

                case RevisarReturnFuncion :
                {
                    if (TA->codigoFamilia == 12) {
                        if (!hayRet) {
                            cout << "No hay return en la funcion "
                                 << TF->lexema << endl ;
                        }
                        usandoFuncion = false;
                    }
                    break;
                }

                case RevisarQueSeUseFuncion :
                {
                    if(TA->codigoFamilia == 29 ){

                        if(!usandoFuncion && !usandoProc){
                            cout << "Se usa return en contexto fuera de funcion o procedimiento"
                                 << " en linea: " << TA->fila << " columnaInicio: " << TA->columnaInicio << " columnaFin: "
                                 << TA->columnaFin << '\n';
                        } else {
                            hayRet = true ;
                        }
                    }
                    break;
                }
                case RevisarCuerpoParaFuncion:
                {
                    if (usandoFuncion) {
                        if (TA->codigoFamilia == 10) {
                            cout << "Return sin cuerpo en la funcion "
                                 << TF->lexema << endl;
                        }
                    }
                    break;
                }
                case RevisarCuerpoParaProc:
                {
                    if (TA->codigoFamilia != 10 && usandoProc)
                    {
                        cout << "Intento de retorno con valor en procedimiento "
                             << TF->lexema << endl ;
                    }
                    break;
                }

                case InicializarVariableProc :
                {
                    if (TA->codigoFamilia == 35 )
                    {
                        usandoProc = true;
                    }
                    break;
                }
                case QuitarIdentificadoresProc :
                {
                    if (TA->codigoFamilia == 12) {
                        usandoProc = false ;
                    }
                    break;
                }
                case GuardarNombreFunc:
                {
                    if (TA->codigoFamilia == 0){
                        TF = TA ;
                    }
                    break;
                }
                case GuardarNombreProc: {
                    if (TA->codigoFamilia == 0) {
                        TF = TA;
                    }
                    break;
                }
                    // REVISAR QUE LOS BLOQUES ESTEN EN SU LUGAR
                case RevisarUsoBloques:
                {
                    if (TA->codigoFamilia == 11){
                        cout << "Uso indebido de bloques"
                             << " en linea: " << TA->fila << " columnaInicio: " << TA->columnaInicio << " columnaFin: "
                             << TA->columnaFin << '\n';
                    }
                    break;
                }

                // REVISAR QUE LOS SECUENCIADORES SE USEN EN CICLOS
                case ActivarSecuenciadores:
                {
                    if (TA->codigoFamilia == 13 || TA->codigoFamilia == 20 || TA->codigoFamilia == 23){
                        secuenciadores = true;
                    }
                    break;
                }

                case DesactivarSecuenciadores:
                {
                    if (TA->codigoFamilia == 10){
                        secuenciadores = false;
                    }
                    break;
                }

                case RevisarSecuenciadores:
                {
                    if ( TA->codigoFamilia == 26 || TA->codigoFamilia ==27 ){
                        if (!secuenciadores){
                            cout << "No se permite el uso de secuenciadores fuera de ciclos"
                                 << " en linea: " << TA->fila << " columnaInicio: " << TA->columnaInicio << " columnaFin: "
                                 << TA->columnaFin << '\n';
                        }
                    }
                }

            }



        }
    }

    PilaParsing.pop();
    if (!PilaParsing.empty()) {
        cout << "Fin de archivo inesperado" << '\n';
        finalizarScanner();
        return 0;
    }

    finalizarScanner();

    if (banderaErrorSintactico || getError())
        return 0;

    cout << "Compilacion terminada.\n";
    return 0;

}

bool esFollow(int i, int j) {
    bool result = false;
    int k = 1;
    while (TablaFollows[i][k] >= 0) {
        if (j == TablaFollows[i][k]) { result = true; }
        k++;
    }
    return result;
}