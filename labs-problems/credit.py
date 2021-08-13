def main():
    num = input("Digite numero do cartao (apenas os numeros): ")
    if checksum(num):
        if len(num) ==  15 and num[0] == '3' and num[1] in ['4' , '7']:
            print("Cartao AMEX ")
        elif len(num) == 16 and num[0] == '5' and num[1] in ['1', '2', '3', '4', '5']:
            print("Cartao MASTERCARD ")
        elif num[0] == '4' and len(num) in [13, 16]:
            print("Cartao VISA ")
        else:
            ("Cartao INVALIDO ")
    else:
        print("Cartao INVALIDO ")

def checksum(num):
    penultimo = len(num) - 2
    mult = []
    for i in range(penultimo, -1, -2):
        mult.append(int(num[i]) * 2)
    arr = []
    ultimo = penultimo + 1
    for i in range(ultimo, -1, -2):
        arr.append(int(num[i]))
    for i in range(len(mult)):
        if mult[i] > 9:
            mult[i] = (mult[i] / 10) - 1
            mult[i] = (mult[i] * 10) + 1
    total = int((sum(mult) + sum(arr)))
    total = str(total)
    if total[len(total) - 1] == '0':
        return True

    return False



if __name__ == "__main__":
    main()