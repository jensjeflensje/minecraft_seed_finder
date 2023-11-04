# Minecraft compatible seed finder

A utility script made in C and Python to find seeds that match biome and size requirements. This project contains functionality that’s already in the website [mcseeder](https://mcseeder.com). The problem is: actual useful seed requirements take ages to process (and the GUI version doesn’t support MacOS). This is a (multithreaded) script which you can host yourself (or just run on your computer).

I originally made the script for my server, [BingoMC](https://bingomc.net). I need multiple different seeds with at least 8 specific biomes in a radius of 2500 blocks for the game to work correctly (otherwise it would be impossible). I store them (pregenerated) in an S3 bucket and download them onto the server once a game boots up.

The script works by generating partials of a seed map (all credits go to https://github.com/Cubitect/cubiomes 😛) and taking samples to see if the biomes match. Seeds will be tried incrementally (1, 2, 3, 4…) and checked to see if it contains all biomes by trying a grid of single coordinates with an amount blocks between them (15 by default).

The script takes some options: the seed range, block radius, step size, and the amount of threads. These settings all dictate how long the script will take. I found that 30 seeds in a radius of 2500 blocks, with a step size of 15, on one thread will take about 1 minute, which I thought was surprisingly fast.

| Setting | Default | Description |
| --- | --- | --- |
| Seed range | 0-200 | The actual range of seeds to match against. More seeds means more processing. |
| Block radius | 2500 | The radius of blocks to look for from X=0 and Z=0. 2500 will be a 5000x5000 area. A larger radius means more processing. |
| Step size | 15 | The amount of blocks that will be in between a sample. A larger number means less processing, but also less accuracy. It’s recommended to keep this below ±35, as you can miss biomes (e.g. rivers) with such a large step size |
| Thread count | 4 | The amount of threads used to divide the workload of the seed range. 200 seeds and 4 threads means each thread does 200 / 4 = 50 seeds. More threads will make things faster, but you can’t set more threads than your computer has logical cores (of course) |


## User guide
Clone this repo:
```shell
git clone --recursive git@github.com:jensjeflensje/minecraft_seed_finder.git
```

The C program has a fixed list of biomes it wants. You can change this.
To compile the program, execute the `compile.sh` script.

When it's successfully compiled, you're able to change the settings (capital letters) in the `check_seeds.py` script, and execute it.

You'll see a file named seeds.txt be created with the found seeds.