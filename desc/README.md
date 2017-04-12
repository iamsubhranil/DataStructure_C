# desc
#### This folder contains user friendly `y/n` questions for each property of an app or library, if any
The `.desc` files have a very simple format :

`PROPERTY=Question`

When the file will be parsed by `scripts/createconfig.sh`, the user will be prompted by the following :

`Question`

`(y/n) > `

If the user selects `y`, the specified `config` file will have a `PROPERTY=y` written in it, and obviously `PROPERTY=n` otherwise.

Multiple corelated properties can also be specified in `PROPERTY1,PROPERTY2=Question` manner, which will result in selection of both `PROPERTY1` and `PROPERTY2` if the user enters `y` to the `Question`.
