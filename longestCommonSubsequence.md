# Given two strings, find length of the longest common subsequence.
## Example: 
String 1: GTACGT

String 2: GGTACA

The length of the longest common subsequence is 4. There are many subsequences that
yield that answer:
* GTAC

## Algorithm
Initialize a maxLength variable to 0.

Compare the first letter of each string. Either they match or they don't match:
* If they match, increment the count variable and erase the first letter of each string
* If they don't, branch (executing both in a parallel universe):
  1. Erase the first letter of string 1 and repeat the process
  2. Erase the first letter of string 2 and repeat the process
  * increment the maxLength variable by the maximum of the returned values 

Return the maxLength variable

### Maintain a 2-d memo array:
|       | G | T | A | C | G | T |
| ----- | - | - | - | - | - | - |
| **G** | 1 | 1 | 1 | 1 | 1 | 1 |
| **G** | 1 | 1 | 1 | 1 | 2 | 2 |
| **T** | 1 | 2 | 2 | 2 | 2 | 3 |
| **A** | 1 | 2 | 3 | 3 | 3 | 4 |
| **C** | 1 | 2 | 3 | 4 | 4 | 4 |
| **A** | 1 | 2 | 3 | 4 | 4 | **4** |

For each row and column (starting at the top left), compare the letters:
* If they match, set the cell equal to `1 + max(left, up)`
* Else, set the cell equal to `max(left, up)`