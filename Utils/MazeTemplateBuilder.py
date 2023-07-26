tamanho = input("Introduza o tamanho do mapa (X x Y): ")
tamanho = tamanho.split(" ")
del tamanho[1]
tamanho = [int(x) for x in tamanho]
height, width = tamanho

print(height, " x ", width)
for i in range(height):
    if i == 0 or i == height-1:
        print("*"*width)
    else:
        print("*"+" "*(width-2) + "*")