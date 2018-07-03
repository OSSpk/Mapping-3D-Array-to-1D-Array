# Mapping 3D Array to 1D Array

## Mapping Formula
If you have a 3D array   **Original[HEIGHT, WIDTH, DEPTH]**   then you could turn it into   **Flat[HEIGHT * WIDTH * DEPTH]**   1D array by

```Flat[x + HEIGHT * (y + WIDTH * z)] = Original[x, y, z], assuming Original[HEIGHT,WIDTH,DEPTH]```

To study more about this, refer to following links: 
* [Row and Column Major Order](https://en.wikipedia.org/wiki/Row-_and_column-major_order)
* [Flatten a 3D array to 1D array](https://stackoverflow.com/questions/7367770/how-to-flatten-or-index-3d-array-in-1d-array)

## Problem
In order to better understand the array mapping, following real life problem is solved: 

![problem](../master/images/p.png)

## Functions Implemented
![problem](../master/images/f.png)


## Contact
You can get in touch with me on my LinkedIn Profile: [Haris Muneer](https://www.linkedin.com/in/harismuneer/)

## Issues
If you face any issue, you can create a new issue in the Issues Tab and I will be glad to help you out.

## License
[MIT](../master/LICENSE)
Copyright (c) 2018-present, harismuneer
