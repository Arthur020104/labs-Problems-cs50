def main():
    while True:
        height = input("Altura da piramide: ")
        h = int(height)
        if h > 0 and h < 9:
            break

    draw(h, h)

def draw(h , space):
    if h == 0:
        return
    draw(h - 1, space)

    print(" " * (space - h), end = "")
    print("#" * h, end = "")
    print("  ", end = "")
    print("#" * h, end = "")
    print()

if __name__ == "__main__":
    main()