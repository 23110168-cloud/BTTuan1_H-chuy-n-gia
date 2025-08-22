# Bài 2: Coloring problem
V = 4  # Số lượng đỉnh trong đồ thị

def print_solution(color):
    print("Lời giải:")
    print(" ".join(map(str, color)))

def is_safe(v, graph, color, c):
    # Kiểm tra xem có thể tô màu c cho đỉnh v hay không
    for i in range(V):
        if graph[v][i] and c == color[i]:
            return False
    return True

def graph_coloring_util(graph, m, color, v):
    # Nếu đã tô màu xong cho tất cả các đỉnh
    if v == V:
        return True
    
    # Thử tô màu từ 1 đến m
    for c in range(1, m + 1):
        if is_safe(v, graph, color, c):
            color[v] = c
            
            # Đệ quy kiểm tra đỉnh kế tiếp
            if graph_coloring_util(graph, m, color, v + 1):
                return True
            
            # Quay lui nếu không tìm thấy lời giải
            color[v] = 0
    
    return False

def graph_coloring(graph, m):
    color = [0] * V  # Mảng lưu màu của các đỉnh
    
    if not graph_coloring_util(graph, m, color, 0):
        print("Noooo")
        return False
    
    print_solution(color)
    return True

if __name__ == "__main__":
    # Minh họa đồ thị
    # (3)---(2)
    #  |  /  |
    #  | /   |
    #  |/    |
    # (0)---(1)
    graph = [
        [0, 1, 1, 1],
        [1, 0, 1, 0],
        [1, 1, 0, 1],
        [1, 0, 1, 0],
    ]
    
    m = 3  # Số màu
    
    graph_coloring(graph, m)
