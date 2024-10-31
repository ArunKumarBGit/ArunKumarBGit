// 0 -                [1]0
//                ___/   \___
//               /           \
// 1 -        [0]0            [1]1
//           /   \           /   \
//          /     \         /     \
// 2 -    [1]0    [0]1    [0]2    [1]3
//        / \     / \     / \     / \
//       /   \   /   \   /   \   /   \
// 3 -  [1] [1] [0] [0] [0] [1] [1] [1]
//       |   |   |   |   |   |   |   |
//       0   1   2   3   4   5   6   7
//
//
// A parent node is 1 iff both child nodes are 1
// bits[level][index]
// N = 4

int tree_node_max[N] =
void 
clear_bits (int start, int length) 
{
    int level = N-1;
    int max_nodes = 0;
    int end = start + length - 1;
    int i = 0;
    int j = 0;

    max_nodes = power(level, 2); // function to get 2-power

    if ((start > level) || (end >= max_nodes)) {
        printf("Invalid parameter\n");
        return;
    }

    // Left_node = parent_node * 2;
    // Right_node = (parent_node * 2) + 1;
    // Parent = child_node/2;
    // Clear parent nodes accordingly :: A parent node is 1 iff both child nodes are 1

    for (i = level; i >= 0; i--) { //2 ; 1
        for (j = start; j <= end; j++) { // 1,2 ; 0
            bits[level][i] = 0;
        }

        start /= 2;     //1 ; 0
        end /= 2;       //2 ; 1
    }

    return;
}
