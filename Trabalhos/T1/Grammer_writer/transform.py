see = open('/home/rodrigo/Documents/Compiladores/Trabalhos/T1/Grammer_writer/input.txt', 'r')

# Read all the file and split it by lines
lines = see.read().splitlines()

for line in lines:
    
    origin = line.split('->')[0]

    line = line.split('->')[1]

    # Split the line by '|'
    line = line.split('|')

    # For each element in the line
    for element in line:

        print(origin + '::= ' + (element.strip() if element.strip() != 'ϵ' else '\'\''))