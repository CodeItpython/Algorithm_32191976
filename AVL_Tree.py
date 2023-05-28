class Node: #노드클래스 정의
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1


class AVLTree:
    def __init__(self): #초기화함수
        self.root = None

    def insert(self, key):  #삽입연산후 노드들을 inorder로 출력
        self.root = self._insert(self.root, key)
        self.print_all_nodes()

    def _insert(self, root, key):   #삽입연산
        if not root:    #루트가 없는경우
            return Node(key)

        if key < root.key: #root.key보다 삽입하려는 key의값이 작을경우
            root.left = self._insert(root.left, key)    #root노드의 왼쪽에 삽입
        else:   #root.key보다 삽입하려는 key의 값이 클경우
            root.right = self._insert(root.right, key) #root노드의 오른쪽에 삽입

        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))#root 노드의 높이

        balance_factor = self.get_balance(root)    #balance_factor값 구하기

        if balance_factor > 1: #balance_factor값이 1보다 클경우 (불균형상태)
            if key < root.left.key: #root의 왼쪽key값이 삽입하려는 key값보다 큰경우
                return self.rotate_right(root)
            else:   #root의 왼쪽값이 삽입하려는 key값보다 작은경우
                root.left = self.rotate_left(root.left)
                return self.rotate_right(root)

        if balance_factor < -1:  #balance_factor값이 -1보다 작을경우 (불균형상태)
            if key > root.right.key:    #root의 오른쪽 key값이 삽입하려는 key값보다 작은경우
                return self.rotate_left(root)
            else: #root의 오른쪽 key값이 삽입하려는 key값보다 큰경우
                root.right = self.rotate_right(root.right)
                return self.rotate_left(root)

        return root

    def delete(self, key):  #삭제연산후에 노드들을 inorder로 출력
        self.root = self._delete(self.root, key)
        print("Node {} deleted".format(key))
        self.print_all_nodes()

    def _delete(self, root, key):
        if not root:    #root노드가 없는경우
            return root

        if key < root.key:  #root.key의값이 삭제하려는 key의값보다 클경우
            root.left = self._delete(root.left, key)
        elif key > root.key:  #root.key의값이 삭제하려는 key의값보다 작을경우
            root.right = self._delete(root.right, key)
        else:
            if not root.left or not root.right:
                if not root.left:
                    temp = root.right
                else:
                    temp = root.left
                root = None
                return temp
            else:
                temp = self.get_min_node(root.right)
                root.key = temp.key
                root.right = self._delete(root.right, temp.key)

        if not root:
            return root

        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

        balance_factor = self.get_balance(root)    #balance_factor 구하기

        if balance_factor >1:#balance_factor가 1보다 큰경우(불균형)
            if self.get_balance(root.left) >= 0:#balance_factor가 왼쪽이 0보다 큰경우
                return self.rotate_right(root) #오른쪽으로회전
            else:
                root.left = self.rotate_left(root.left)
                return self.rotate_right(root)

        if balance_factor < -1:#balance_factor가 -1보다 작은경우(불균형)
            if self.get_balance(root.right) <= 0:
                return self.rotate_left(root)
            else:
                root.right = self.rotate_right(root.right)
                return self.rotate_left(root)

        return root

    def search(self, key):  #탐색연산
        return self._search(self.root, key)

    def _search(self, root, key):
        if not root or root.key == key:
            return root

        if key < root.key:  #root.key가 탐색하려는 key의값보다 클경우
            return self._search(root.left, key)
        else:   #root.key가 탐색하려는 key의 값보다 작을경우
            return self._search(root.right, key)

    def get_height(self, root):    #각 노드의 높이 구하기
        if not root:
            return 0
        return root.height

    def get_balance(self, root):   #각 노드의 balance factor 구하기
        if not root:
            return 0
        return self.get_height(root.left) - self.get_height(root.right)


    def rotate_left(self, z):  #왼쪽으로 회전
        # z의 오른쪽 자식은 변수 a에 할당되고 a의 왼쪽 자식은 b에 할당됨
        a = z.right
        b = a.left

        # a의 왼쪽 자식은 z로 업데이트되고 z의 오른쪽 자식은 b로 업데이트됨
        a.left = z
        z.right = b

        # 마지막으로 회전된 하위 트리의 새 루트인 a를 반환
        z.height = 1 + max(self.get_height(z.left), self.get_height(z.right))
        a.height = 1 + max(self.get_height(a.left), self.get_height(a.right))

        return a

    def rotate_right(self, z): #오른쪽으로 회전
        # z의 왼쪽 자식은 변수 a에 할당되고 a의 오른쪽 자식은 b에 할당됨
        a = z.left
        b = a.right

        # a의 오른쪽 자식은 z로 업데이트되고 z의 왼쪽 자식은 b으로 업데이트됨
        a.right = z
        z.left = b

        # z 및 a의 높이는 왼쪽 및 오른쪽 하위 트리의 높이를 기준으로 다시 계산됨
        # 회전된 하위 트리의 새 루트인 a를 반환
        z.height = 1 + max(self.get_height(z.left), self.get_height(z.right))
        a.height = 1 + max(self.get_height(a.left), self.get_height(a.right))

        return a

    def get_min_node(self, root):  #최소노드 구하기
        if root.left is None:
            return root
        return self.get_min_node(root.left)

    def print_all_nodes(self):  #노드를 inorder방식으로 출력
        self.inorder(self.root)
        print()

    def inorder(self, root):    #inorder로 출력
        if root:
            self.inorder(root.left)
            print(root.key, end=" ")
            self.inorder(root.right)



if __name__ == "__main__":
    avl_tree = AVLTree()

    # key삽입
    avl_tree.insert(10)
    avl_tree.insert(5)
    avl_tree.insert(15)
    avl_tree.insert(3)
    avl_tree.insert(7)
    avl_tree.insert(12)

    # key 검색
    key_to_search = 7
    result = avl_tree.search(key_to_search)
    if result:
        print("Key {} is found".format(key_to_search))
    else:
        print("Key {} is not found".format(key_to_search))

    # key 삭제
    key_to_delete = 5
    avl_tree.delete(key_to_delete)
    print("Key {} has been deleted".format(key_to_delete))

    # 삭제한 key검색
    result = avl_tree.search(key_to_delete)
    if result:
        print("Key {} is found".format(key_to_delete))
    else:
        print("Key {} is not found".format(key_to_delete))