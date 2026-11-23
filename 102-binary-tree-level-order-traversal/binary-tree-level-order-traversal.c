
int** levelOrder(struct TreeNode* root, int* returnSize,
                 int** returnColumnSizes) {

    *returnSize = 0;
    *returnColumnSizes = NULL;

    if (root == NULL)
        return NULL;

    int** result = malloc(2000 * sizeof(int*));
    *returnColumnSizes = malloc(2000 * sizeof(int));

    struct TreeNode* queue[2000];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {

        int size = rear - front;

        result[*returnSize] = malloc(size * sizeof(int));
        (*returnColumnSizes)[*returnSize] = size;

        for (int i = 0; i < size; i++) {

            struct TreeNode* temp = queue[front++];

            result[*returnSize][i] = temp->val;

            if (temp->left)
                queue[rear++] = temp->left;

            if (temp->right)
                queue[rear++] = temp->right;
        }

        (*returnSize)++;
    }

    return result;
}
