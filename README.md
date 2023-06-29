# miniRT

This project is an introduction to the beautiful world of Raytracing.

## Renders

See `doc/renders` for more

![Untitled](miniRT%204b5d216adc884f35b054cdbcb65eb6ee/Untitled.png)

**Usage**
First clone the repository and the git submodules:

`git clone --recurse-submodules -j8 git@github.com:Hugothms/miniRT.git`

Then make and run the executable:

`make && ./miniRT scenes/test.rt`

Or, you can make and run more conveniently:

`make test`

## How to install

1. Clone the repo:

`git@github.com:nesvoboda/minirt.git --recursive`

1. `cd` into it and `make` to compile it:

`cd minirt && make`

1. Now `./miniRT ./scenes/scene.rt`

There are some scenes in the `scenes` folder that showcase minirt.

## Known Issues

It has been suggested that the color model is slightly inaccurate.