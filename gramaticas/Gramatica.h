/*
 * Gramatica.h
 *
 * 2018/05/19 03:15:58
 *
 * Archivo generado por GikGram 2.0
 *
 * Copyright © Olminsky 2011 Derechos reservados
 * Reproducción sin fines de lucro permitida
 */
#pragma once

#ifndef INC_Gramatica_h_
	#define INC_Gramatica_h_

	/* Constantes necesarias para un driver de parsing */
	#define TERMINAL(X)  ((0 <= (X)) && ((X) <= 118))
	#define NO_TERMINAL(X)  ((119 <= (X)) && ((X) <= 241))
	#define MARCA_DERECHA 118
	#define NO_TERMINAL_INICIAL 119
	#define MAX_LADO_DER 14

	/* Constantes con las rutinas semánticas */
	#define InicializarVariableReturn 242
	#define GuardarNombreFunc 243
	#define RevisarReturnFuncion 244
	#define InicializarVariableProc 245
	#define GuardarNombreProc 246
	#define QuitarIdentificadoresProc 247
	#define RevisarUsoBloques 248
	#define RevisarSecuenciadores 249
	#define DesactivarSecuenciadores 250
	#define EmpujarFalsoNakhaan 251
	#define BotePilaNakhaan 252
	#define RevisarDefault 253
	#define ActivarSecuenciadores 254
	#define RevisarQueSeUseFuncion 255
	#define RevisarCuerpoParaFuncion 256
	#define RevisarCuerpoParaProc 257

	/* Prototipos de las tablas */
	extern const int TablaParsing[123][NO_TERMINAL_INICIAL];
	extern const int LadosDerechos[267][MAX_LADO_DER];

#endif /* INC_Gramatica_h_ */
