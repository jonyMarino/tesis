# tesis

Este repositorio contiene submódulos por lo que es recomendable clonarlo así:
`git clone --recursive https://github.com/jonyMarino/tesis.git`

Para saber como está estructurado este repositorio ver el apéndice de la tesis que se encuentra en tesis.pdf


La siguiente es una guía orientativa para compilar y utilizar los proyectos que se encuentran en las carpetas del repositorio:

Casi todo se puede compilar y correr desde consola salvo generar el código
desde UML que sólo se puede con el Eclipse abierto (en realidad también hay una
forma de prescindirlo pero  no exploré como).

Para compilar el generador de código desde UML y para facilitar su uso se precisa Eclipse Mars o Luna (preferentemente Mars y **no** versiones más actuales) y opcionalmente con Papyrus (Un editor UML gráfico para ver los diagramas de
mejor manera). Del resto de las cosas se encarga maven.

Para importar los proyectos desde eclipse tiene se debe seleccionar Import
-> General -> Existing projects into Workspace y seleccionar la
carpeta de la tesis.
No importe los proyectos org.eclipse... salvo el que termina
.embedded.c si quiere ver el código del generador en Acceleo.

Los proyectos DynaceDemo y COSDemo precisan instalar Dynace y COS
respectivamente. Los mismos fueron incluidos en git por lo que si
clonó con la opción --recursive se encuentran al lado del proyecto de
ejemplo de cada uno.

Por ejempplo, para compilar COS ir a ejemplos_de_codificacion_para_cada_framework/COS/COS y ejecutar ```make```.
Después de eso va a poder compilar el ejemplo de COS en COSDemo
ejecutando ```make``` dentro de la carpeta COSDemo.

Para compilar el generador de código ir a
generador_de_codigo_para_SOOPC_OOC_Y_DYNACE/UML2ooec/releng/org.eclipse.umlgen.gen.embedded.c.build
y ejecutar desde consola `mvn clean package`
Luego de esto se generan los plugins del generador que pueden ser
instalados en eclipse (Luna o Mars). Los mismos se encuentrarán en
/releng/org.eclipse.umlgen.gen.embedded.c.repository/target/repository/
Para instalarlos en eclipse se debe ir a Help->install new software->
add... -> file -> y seleccionar la ubicación anterior.
Luego marcar el checkbox de Eclipse UML Generators y presionar Finish.

Luego en los demos de SOOPC, OOC de Miseta y Dynace se puede generar
el código desde el UML de cada proyecto (básicamente botón derecho en
el proyecto demo-> Run as...->run configurations-> UML to Embedded C
Generation y si no aparece una configuración ya generada en UML model
se selecciona el archivo .uml en el proyecto demo y en Output folder
path: la carpeta de salida que siempre se llama src-gen


La documentación de como utilizar el generador original se encuentra
[aquí]( https://www.eclipse.org/umlgen/documentation/releases/1.0.0/org.eclipse.umlgen.gen.embedded.c.doc/embedded_C-generator/user/user-guide.html)

Para el prototipo de "generador" para OOPC se precisa instalar Acceleo. Una vez instalado importar el proyecto org.eclipse.acceleo.module.oopc que se encuentra
en la carpeta consultas_para_un_generador_de_codigo_para_OOPC/
Luego en Run as...->Run configurations ->Acceleo Application (si no
existe una configuración hacer doble click
y llenar el formulario con Main class:
org.eclipse.acceleo.module.oopc.main.Generate
Model: /org.eclipse.acceleo.module.oopc/model/model.uml
target: /org.eclipse.acceleo.module.oopc/src-gen)
presionar en Finish y ver el código generado en src-gen
