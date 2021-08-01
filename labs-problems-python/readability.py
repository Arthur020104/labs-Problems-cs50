from cs50 import get_string

def main():
    texto = get_string("Digite um texto: ")
    total = gralvl(texto)
    print(f"Grade level is {total}")

def gralvl(texto):
    total =[1, 0, 0]
    for i in texto:
        if i in [" "]:
            total[0] += 1
        elif i in ["?", "!" , "."]:
            total[1] += 1
        elif not i in [" ", "?", "!" ,"."]:
            total[2] += 1
    si = 100 *(total[1]/total[0])
    l = 100 *(total[2]/total[0])
    g = (0.0588 * l) - (0.296 * si) - 15.8
    g = round(g)
    if g > 16:
        g = "+16"
    elif g < 1:
        g = "-1"
    return g
if __name__ == "__main__":
    main()