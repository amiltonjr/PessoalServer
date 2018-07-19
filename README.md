SERVIDOR API - CADASTRO DE PESSOAL

Objetivo: O objetivo deste servidor é receber os dados de um aplicativo mobile e
imprimi-los na tela do terminal Unix.

Autor: Amilton Fontoura de Camargo Junior
Data de produção: Julho de 2018

Recursos Utilizados:
	IDE: Qt Creator 4.7.0-rc1
	Biblioteca externa: QtWebServer 3.11.0 - Autor: Stefan Frings
	Padrão API: Swagger 2.0

Classe principal:
	server/src/main.cpp

Classe de controle da API:
	server/src/controller/apicontroller.cpp

Arquivo de configuração do servidor:
	server/etc/Server.ini

Arquivos de modelo da API:
	Model/swagger.yaml
	swagger.json
