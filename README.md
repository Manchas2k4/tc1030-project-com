![Tec de Monterrey](images/logotecmty.png)
# Situación problema: Simulación de un sistema de comunicación celular.

## <span style="color: rgb(26, 99, 169);">¿Qué tengo que hacer?</span>
En este repositorio encontrarás una serie de carpetas y archivos que necesitarás para el desarrollo del proyecto.
* *test_cases*: En este directorio encontrarás los archivos de entrada (`input0.txt`, `input1.txt`, `input2.txt`, `input3.txt`, `input4.txt`, `input5.txt`, `input6.txt`) que utilizaremos para probar el sistema completo. Adicionalmente están las salida esperadas para cada uno de los archivos de entrada (`output0.txt`, `output1.txt`, `output2.txt`, `output3.txt`, `output4.txt`, `output5.txt`, `output6.txt`).
* *unit_test*: En este directorio se encuentran los archivos de pruebas de unidad para cada una de las clases que tienes que desarrollar. Estos archivos de prueba te permiten verificar si tu implementación es correcta.
* *archivos cabecera (o header)*: Archivos en los que se realiza la implementación de cada clase.
* `main.cpp`: Archivo que contiene la función `main`. En este archivo se realiza la lectura/escritura de archivos.

En estos archivos deberás desarrollar la implementación de cada una de las clases que integran la solución del problema presentado en esta actividad. En la parte superior de cada archivo coloca deberás, en comentarios, tus datos. Por ejemplo:
```
// =========================================================
// File: one_header.h
// Author: Edward Elric - A00123456
// Date: 01/01/2021
// Description: This file implements some functions.
// =========================================================
```

## <span style="color: rgb(26, 99, 169);">Introducción</span>
Cómo, de seguro, ya habrás oído, vivimos en un mundo donde las revoluciones tecnológicas ocurren todos los días. Una de las revoluciones más importantes fue, sin lugar a dudas, los sistemas de comunicación celular. En este proyecto, vamos a implementar una versión simple de un sistema de comunicación celular.

En este sistema existen *clientes*, *operadores* y *facturas* que pertenecen a un cliente determinado. Los clientes pueden hablar entre ellos, enviarse mensajes o conectarse a Internet a través de sus dispositivos móviles. Los operadores tienen costos únicos para todas estas acciones. Cada cliente tendrá una única factura que almacena y realiza las operaciones necesarias sobre sus gastos.

Tu solución tomará la entrada de un archivo de texto, realizará las operaciones e imprimirá la información necesario en un archivo de texto de salida. El nombre de ambos archivos, los tomará como argumento del programa. En otras palabras, **no habrá ninguna entrada dada con el teclado mientras se ejecuta el programa**.

Ten en cuenta que habrá varias clases. Por lo tanto, trabajarás con varios archivos cabecera (o header). Los nombres de las variables de instancia y métodos se proporcionarán en este documento, así como en el encabezado de la clase que se encuentra en cada archivo cabecera. Aunque esto no significa que no puedas agregar métodos o campos adicionales.

### <span style="color: rgb(26, 99, 169);">**Clases**</span>
Existen 5 clases interactuando entre sí en este proyecto:
* `Customer`.
* `Operator`.
* `VoxOperator` (derivado de `Operator`).
* `InternetOperator` (derivado de `Operator`).
* `Bill`.

Ten en cuenta que será necesario hacer los cálculos necesarios mediante el uso de los métodos correspondiente en las clases `Customer`, `Operator` (y derivados) o `Bill`, no en el programa principal.

#### <span style="color: rgb(26, 99, 169);">**Bill**</span>
La clase `Bill` cuenta con las siguientes variables de estado:
* `limitAmount` : Límite de crédito.
* `currentDebt` : Deuda actual.
* `totalMoneySpent` : Dinero total que el cliente ha pagado a lo largo del tiempo.

La clase cuenta con los siguientes métodos:
* Constructor con un parámetro (el límite de crédito). Este método deberá inicializar el resto de variables a 0.
* Constructor de copia.
* Métodos de acceso para todas las variables de instancia. (Si consideras necesario agregar métodos de modificación, adelante).
* `add(double amount)`: Agrega cargos a la factura. Si la cantidad es menor o igual 0, no deberá hacer cambios.
* `pay(double amount)`: Reduce la deuda en la cantidad dada. Si la cantidad es menor o igual a 0, no deberá hacer cambios. Nunca se podrá pagar más cantidad que la deuda actual.
* `changeTheLimit(double amount)`: Cambia el límite de crédito, siempre y cuando sea mayor a la deuda actual. Si la cantidad es menor o igual a 0, no deberá hacer cambios.
* `check(double amount)`: Regresa verdadero si la cantidad más la deuda actual no existe el límite de crédito.

#### <span style="color: rgb(26, 99, 169);">**Operator**</span>
Si bien, existen dos tipos de operadores, aquellos que dan un mayor soporte a llamadas y mensajes(*VOX*) y aquellos que dan un mayor soporte al uso de Internet (*INTERNET*), todos comparte características comunes. La clase `Operator` define estas características. Las variables de estado con las que cuenta son:
* `id`: Identificador único del operador.
* `discountRate`: Porcentaje de descuento a aplicar.
* `talkingCharge`: El costo por minuto de llamada.
* `messageCost`: El costo por envío de mensaje.
* `networkCharge`: El costo por GB utilizado.
* `totalSpentTalkingTime`: El tiempo total que se ha empleado en llamadas.
* `totalMessageSent`: Los mensajes totales que se han enviado.
* `totalInternetUsage`: El total de GB's utilizados.
* `type`: Tipo de operador (VOX o INTERNET).

La clase cuenta con los siguientes métodos:
* Constructor con 6 parámetros. Recibe el id, el costo por minuto de llamada, el costo por envío de mensaje, el costo por GB, el porcentaje de descuento y el tipo de operador. El resto de las variables debe inicializarse a 0.
* Constructor de copia.
* Métodos de acceso para todas las variables de instancia. (Si consideras necesario agregar métodos de modificación, adelante).
* `addTalkingTime(int minute)`: Si la cantidad es mayor a 0, agrega la cantidad al tiempo total que se ha empleado en llamadas.
* `addTotalMessageSent(int quantity)`: Si la cantidad es mayor a 0, agrega la cantidad al total de mensajes enviados.
* `addTotalInternetUsage(double amount)`: Si la cantidad es mayor a 0, agrega la cantidad a los GB's totales empleados.
* `toString()`: Regresa un string con el siguiente formato: "Operator #id : totalSpentTalkingTime totalMessageSent addTotalInternetUsage". Todas las cantidades de punto flotantes deben tener una precisión de dos números decimales.
* `virtual double calculateTalkingCost(int, int) = 0;`: Función virtual. Debe ser implementada en las clases derivadas.
* `virtual double calculateMessageCost(int, int, int) = 0;`: Función virtual. Debe ser implementada en las clases derivadas.
* `virtual double calculateNetworkCost(double) = 0;`: Función virtual. Debe ser implementada en las clases derivadas.

#### <span style="color: rgb(26, 99, 169);">**VoxOperator**</span>
Este tipo de operador se especializa en aquellas personas que hacen un uso más intensivo de las llamadas y los mensajes de texto. Deriva de `Operator`.

La clase cuenta con los siguientes métodos:
* Constructor con 6 parámetros. Recibe el id, el costo por minuto de llamada, el costo por envío de mensaje, el costo por GB, el porcentaje de descuento y el tipo de operador. Debe invocar al constructor de la clase superior.
* Constructor de copia. Debe invocar al constructor de la clase superior.
* `calculateTalkingCost(int minute, int age)`: Si la cantidad de minutos o la edad es menor igual a 0, regresará 0. En caso contrario, calcula el costo de la llamada tomando en cuenta el costo por minuto definido. Si la persona es menor a 18 o mayor a 65, le aplica el descuento definido.
* `double calculateMessageCost(int quantity, int thisOpId, int otherOpId)`: Si la cantidad de mensajes es menor igual a 0, regresará 0. En caso contrario, calcula el costo de enviar los mensajes tomando en cuenta el costo por envío definido. Si los mensajes son enviados al mismo operador, le aplica el descuento definido.
* `calculateNetworkCost(double amount)`: Si la cantidad de GB es mayor a 0, calcula el costo por GB.

#### <span style="color: rgb(26, 99, 169);">**InternetOperator**</span>
Este tipo de operador se especializa en aquellas personas que hacen un uso más intensivo de Internet. Deriva de `Operator`.

La clase cuenta con los siguientes métodos:
* Constructor con 6 parámetros. Recibe el id, el costo por minuto de llamada, el costo por envío de mensaje, el costo por GB, el porcentaje de descuento y el tipo de operador. Debe invocar al constructor de la clase superior.
* Constructor de copia. Debe invocar al constructor de la clase superior.
* `calculateTalkingCost(int minute, int age)`: Si la cantidad de minutos o la edad es menor igual a 0, regresará 0. En caso contrario, calcula el costo de la llamada tomando en cuenta el costo por minuto definido. Si la cantidad de minutos es menor a 2, le aplica el descuento definido.
* `double calculateMessageCost(int quantity, int thisOpId, int otherOpId)`: Si la cantidad de mensajes es menor igual a 0, regresará 0. En caso contrario, calcula el costo de enviar los mensajes tomando en cuenta el costo por envío definido. Si la cantidad de mensajes enviados es menor a 3, le aplica el descuento definido.
* `calculateNetworkCost(double amount)`: Si la cantidad de GB es menor o igual a cero, regresará 0. Sólo se cobrará la cantidad de GB que exceda el limite de 1 GB.

#### <span style="color: rgb(26, 99, 169);">**Customer**</span>
La clase `Customer` cuenta con las siguientes variables de estado:
* `id` : Identificador del cliente.
* `name`: Nombre del cliente.
* `age` : Edad del cliente.
* `totalSpentTalkingTime`: El tiempo total que este cliente ha empleado en llamadas.
* `totalMessageSent`: Los mensajes totales que este cliente ha enviado.
* `totalInternetUsage`: El total de GB's utilizados por este cliente.
* `op`: Apuntador a un objeto de la clase Operator. El operador que da servicio a este cliente.
* `bill`: Apuntador a un objeto de la clase Bill. La factura del cliente.

La clase cuenta con los siguientes métodos:
* Constructor con 5 parámetros. Recibe el id, el nombre, la edad, el operador y el límite de crédito. Se debe crear el objeto de la clase *Bill*.
* Constructor de copia.
* Destructor. Debe eliminar la factura. Todos los apuntadores debe ser igualados a nulo.
* Métodos de acceso para todas las variables de instancia. (Si consideras necesario agregar métodos de modificación, adelante).
* Método de modificación para la variable *op*.
* `talk (int minutes, Customer &other)`: Si la cantidad es mayor a 0 y `other` es un cliente diferente, se calcula el costo por los minutos que duró la llamada. Si todavía hay límite de crédito en la factura, deberá agregar el costo a la factura y agregar los minutos empleados al conteo de nuestro cliente y su operador. Si el operador de nuestro cliente y el `other`son diferentes, también deberá de agregarse esta cantidad al otro operador.
* `message(int quantity, const Customer &other)`: Si la cantidad es mayor a 0 y `other` es un cliente diferente, se calcula el costo por los mensajes enviados. Si todavía hay límite de crédito en la factura, deberá agregar el costo a la factura y agrega los mensajes enviados en el conteo del cliente y del operador.
* `connection(double amount)`: Si la cantidad es mayor a 0, se calcula el costo por el uso de Internet. Si todavía hay límite de crédito en la factura, deberá agregar el costo a la factura y agrega los GB utilizados tanto en el conteo del cliente y del operador.
* `toString()`: Regresa un string con el siguiente formato: "Customer #id : totalMoneySpend currentDebt". Todas las cantidades de punto flotantes deben tener una precisión de dos números decimales.

#### <span style="color: rgb(26, 99, 169);">**main.cpp**</span>
En el archivo *main.cpp* se realizarán las operaciones generales de entrada y salida. Leerás de un archivo de entrada las operaciones sobre la simulación, las deberás realizar e imprimirás los resultados en el archivo de salida.

Las operaciones se detallan más adelante. El nombre de los archivos de entrada y salida se darán como argumentos del programa a través de la línea de comandos. Si el archivo de entrada no existe, el programa termina.

Deberás manejar dos vectores, uno para apuntadores a objetos `Customer` y otro para apuntadores a objetos `Operator`.

#### <span style="color: rgb(26, 99, 169);">**Entrada**</span>
Vas a leer el archivo de entrada elemento por elemento.

La primera línea tiene tres números enteros, `C`, `O` y `N`. El número `C` represnta el número de clientes que estarán en la simulación. El segundo número, `O`, indica el número de operadores en la simulación. El tercer número, `N`, representa el número de eventos a simular.

Las siguientes `N` líneas serán algunas de las siguientes operaciones:
1. Creando un nuevo cliente.
2. Creando un nuevo operador.
3. Un cliente puede hablar con otro cliente.
4. Un cliente puede enviar un mensaje a otro cliente.
5. Un cliente puede conectarse a Internet.
6. Un cliente puede pagar sus facturas.
7. Un cliente puede cambiar de operador.
8. Un cliente puede cambiar su límite de Factura.

##### <span style="color: rgb(26, 99, 169);">**1. Creando un nuevo cliente**</span>
Esta línea contiene un 1 seguido del nombre del cliente, la edad, el identificador del operador y la cantidad límite de crédito del cliente.

```
1 <name> <age> <opeatorId> <limitingAmount>
```
Toma en cuenta que el identificador del cliente será el orden de creación. Por ejemplo, el primer cliente creado debe tener id 0 y debe colocarse la posición 0 del vector. Además, no existe ninguna operación para crear un objeto `Bill` (lo debes realizar en el constructor del cliente).

##### <span style="color: rgb(26, 99, 169);">**2. Creando un nuevo operador**</span>
Esta línea contiene un 2 seguido del tipo de operador (1 = VOX, 2 = INTERNET), cargo por llamada, cargo por mensaje, cargo por uso de internet y el descuento a aplicar.

```
2 <opType> <talkingCharge> <messageCost> <networkCharge> <discountRate>
```
Toma en cuenta que el identificador del operador será el orden de creación. Por ejemplo, el primer operador creado debe tener Id 0 y debe colocarse en la posición 0 del vector.

##### <span style="color: rgb(26, 99, 169);">**3. Un cliente puede hablar con otro cliente**</span>
Esta línea contiene un 3 seguido del id del primer cliente (origen), el id del segundo cliente (destino) y el tiempo de la llamada.

```
3 <idCustomer1> <idCustomer2> <time>
```
##### <span style="color: rgb(26, 99, 169);">**4. Un cliente envía un mensaje a otro cliente**</span>
Esta línea contiene un 4 seguido del id del primer cliente (origen), el id del segundo cliente (destino) y la cantidad de mensajes enviados.

```
4 <idCustomer1> <idCustomer2> <quantity>
```

##### <span style="color: rgb(26, 99, 169);">**5. Un cliente se conecta a Internet**</span>
Esta línea contiene un 5 seguido del id del cliente y la cantidad de Internet utilizada en GB.

```
5 <idCustomer> <amount>
```

##### <span style="color: rgb(26, 99, 169);">**6. Un cliente paga sus facturas**</span>
Esta línea contiene un 6 seguido del id del cliente y la cantidad de dinero que el cliente quiere pagar.

```
6 <idCustomer> <amount>
```
##### <span style="color: rgb(26, 99, 169);">**7. Un cliente cambia de operador**</span>
Esta línea contiene un 7 seguido del id del cliente y el id del operador.

```
7 <idCustomer> <idOperator>
```
##### <span style="color: rgb(26, 99, 169);">**8. Un cliente cambia su límite de factura**</span>
Esta línea contiene un 8 seguido del id del cliente y el nuevo límite.

```
8 <idCustomer> <amount>
```
#### <span style="color: rgb(26, 99, 169);">**Salida**</span>
Debes calcular lo siguiente e imprimirlo en el archivo de salida.

Por cada operador, debes imprimir la cantidad de tiempo de llamadas que atiendieron, la cantidad de mensajes enviados a través de ese operator y la cantidad de uso de Internet en términos de GB proporcionados por el operador.
```
Operator <id>:  <talkingTime> <totalMessages> <totalMBs>
```

Por cada cliente, debes imprimir cuánto dindero ha gastado en pagar su factura y la deuda actual al final de la simulación.
```
Customer <id>:  <totalMoneySpend> <currentDebt>
```
Posteriormente, desplegar el id del cliente que más habla y la cantidad de tiempo en minutos (si dos clientes son iguales, debes imprimir el que tiene una id más pequeña).
```
<name of the customer>:  <total talking time>
```
A continuación, desplegar el id del cliente que más mensajes envía y la cantidad de mensajes enviados (si dos clientes son iguales, debes imprimir el que tiene una id más pequeña).
```
<name of the customer>:  <number of messages>
```
En seguida, desplegar el id del cliente que más se conecta a Internet y la cantidad de GBs (si dos clientes son iguales, debes imprimir el que tiene una id más pequeña).
```
<name of the customer>: <connection amount>
```
Por último, deberás eliminar todos los apuntadores que existan y cerrar los archivos de entrada y salida.
