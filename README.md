# Router CNC

+ ## Descrição geral do sistema:

  + O sistema 

    + #### Diagrama de blocos do sistema:

      <p align="center">
        <img width="540" height="320" src="">
      </p>

    + #### Diagrama esquemático do sistema:
    
    <p align="center">
     <img width="540" height="320" src="">
     </p>
     
+ ## Interface

  + O bloco de interface contém um display LCD 16x2 e 4 botões além da Interface Serial. 
  
  
   + O display apresenta 5 telas, sendo elas a tela inicial, de erro, de referenciamento, de posição e de fim de curso               positivo, as quais serão explicadas na seção **Funcionamento**. 

    + Os botões do teclado servem para:
      + P: Ativar/Desativar e Selecionar eixo para movimento manual.
      + +: Movimenta eixo no sentido positivo, horário (CW).
      + -: Movimenta eixo no sentido negativo, anti-horário (CCW)
      + S: Liga spindle em manual.
      
    + Se o modo manual não estiver ativado, o controlador aceita comandos pela entrada
      serial, os comandos permitidos são listados abaixo:
      
| Eixo    | Comando        | Descrição                                                                                                                                                                                                                            | Exemplo                                                                                                               |
|---------|----------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------|
| Spindle | S=             | Ajusta a velocidade (em RPM) de giro do eixo Spindle.<br>Limites:<br>Mínimo: 200 RPM<br>Máximo: 2000 RPM                                                                                                                             | S=1000<br>Ajusta a velocidade<br>em 1000RPM, mas<br>não liga o eixo.                                                  |
|         | M3             | Liga o eixo spindle no sentido CW                                                                                                                                                                                                    |                                                                                                                       |
|         | M4             | Liga eixo spindle no sentido CCW                                                                                                                                                                                                     |                                                                                                                       |
| Eixos   | F=             | Modifica a velocidade de movimento dos eixos X, Y e Z.<br><br>Lento, Medio, Rapido                                                                                                                                                   | F=Medio<br>Ajusta a velocidade<br>de deslocamento<br>para a velocidade<br>média, mas não<br>movimenta nenhum<br>eixo. |
|         | X=<br>Y=<br>Z= | Comanda o movimento para o eixo<br>especificado.<br>Caso mais de um eixo seja comandado na<br>mesma mensagem, os eixos deve ser<br>interpolados linearmente, válido somente<br>para os eixo X e Y.<br>*Respeitar os limites de curso | X=100<br>Move o eixo X para<br>a posição 100<br>X=10Y=5<br>Move ambos os<br>eixos com<br>interpolação linear.         |



      <p align="center">
        <img width="440" height="220" src="">
      </p>


+ ## Funcionamento

  + 

    <p align="center">
     <img width="540" height="320" src="">
     </p>
  
  
+ ## Periféricos

  + **Chaves e Sensores:** São utilizadas chaves normalmente abertas para simular o comportamento dos sensores de referência (Home) e de proteção aberta (Cover Closed).
  + **MCU:** ...
  + **Driver:** O driver utilizado é o circuito integrado L293D - Quadruple Half-H Drivers.
  + **Motor dos eixos** São utilizados motores de passo bipolares.
  + **Spindle** O motor do Spindle é simulado com um Motor DC unipolar e um encoder de 20PPR. A velocidade atual, não a programada, é mostrada no display da interface.
  + **Heart Beat:** Um LED foi utilizado para informar que o sistema está em execução. O LED permanece aceso caso o driver de saída esteja desabilitado.

+ ## Controlador
  + O controlador utilizado foi do tipo Proporcional, neste controlador o sinal de erro,
diferença entre o sinal de referência e o sinal de realimentação, é multiplicado pelo ganho
proporcional (Kp) e aplicado a saída.

    <p align="center">
      <img width="440" height="220" src="diagrams/proportional_controller.PNG">
    </p>

   + #### Diagrama de blocos do controlador:
   
<p align="center">
<img width="540" height="320" src="diagrams/controller_block_diagram.PNG">
</p>


+ ## Software
  
  + **IDE:** A IDE utilizada foi a [Sloeber](https://eclipse.baeyens.it/), IDE do Eclipse para Arduino.
  + **Bibliotecas utilizadas:** LiquidCrystal, [Bounce2](https://github.com/thomasfredericks/Bounce2) e as bibliotecas criadas contidas em [myLibs](https://github.com/jessenKS/Router-CNC/tree/master/myLibs).
  + **Arquivo .hex:** Ao compilar a aplicação, os arquivos .hex e .elf ficam localizados na pasta Release.
    

+ ## Autores

* **Felipe Tavares** - [felipe-tavares](https://github.com/felipe-tavares)
* **Jessen Krupinski Scariot** - [jessenKS](https://github.com/jessenKS)
