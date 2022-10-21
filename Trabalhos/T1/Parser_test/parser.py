from curses.ascii import islower
import xml.etree.ElementTree as ET
import re

# parse XML file into ElementTree object


def parse_xml(filename):
    tree = ET.parse(filename)
    root = tree.getroot()
    return root

# get all states from XML file


def get_states(root):
    states = []
    for state in root.iter('state'):
        states.append(state.get('id'))
    return states

# get all transitions from XML file


def get_transitions(root):
    transitions = []
    for transition in root.iter('transition'):
        transitions.append((transition.find('from').text, transition.find(
            'to').text, transition.find('read').text))
    return transitions

# get all final states from XML file


def get_final_states(root):
    final_states = []
    for state in root.iter('state'):
        if state.find('final') is not None:
            final_states.append(state.get('id'))
    return final_states

# get all initial states from XML file


def get_initial_states(root):
    initial_states = []
    for state in root.iter('state'):
        if state.find('initial') is not None:
            initial_states.append(state.get('id'))
    return initial_states

# get all symbols from XML file


def get_symbols(root):
    symbols = []
    for transition in root.iter('transition'):
        if transition.find('read').text not in symbols:
            symbols.append(transition.find('read').text)
    return symbols


def expand_re(regex):
   expansion = []

   for i in range(0, 255):
    if(re.match(regex, chr(i))):
        expansion.append(chr(i))
        if(islower(i)):
            expansion.append(chr(i).upper())
   return expansion
    
def main():

    ascii_range = 256
    
    root = parse_xml('/home/rodrigo/Documents/Compiladores/Trabalhos/T1/Parser_test/sofrimento.jff')
    transitions = get_transitions(root)

    matrix = [[0 for x in range(ascii_range)] for y in range(len(get_states(root)) + 1)]

    matrix[1][32] = 171
    for i in range(2,144):
        for j in range(65, 91):
            matrix[i][j] = 172
        for j in range(97, 123):
            matrix[i][j] = 172
            
    
    for transition in transitions:

        list = expand_re(transition[2])
        for item in list:
            matrix[int(transition[0])][ord(item)] = transition[1]

    print('int initial_state = ' + get_initial_states(root)[0] + ';\n')

    max_state = 0
    for state in get_states(root):
        if (int(state) > max_state):
            max_state = int(state)

    if ascii_range > max_state:
        digits = len(str(ascii_range))
    else:
        digits = len(str(max_state))

    print('int transistions_table[' + str(len(get_states(root)) + 1) + '][' + str(ascii_range) + '] = {')

    print('/*' + ' ' * (digits + 8), end='')
    for i in range(ascii_range):
        if i < 32 or i > 126:
            print(str(i).rjust(digits), end='')
        else:
            print(chr(i).rjust(digits), end='')
        if (i != ascii_range - 1):
            print('  ', end='')
    print('*/')
    
    for i in range(len(get_states(root)) + 1):
        print('/* {} */\t{{'.format(str(i).rjust(digits)), end='')
        for j in range(ascii_range):
            print('{}'.format(str(matrix[i][j]).rjust(digits)), end='')
            if (j != ascii_range - 1):
                print(', ', end='')
        print('}', end='')
        if (i != len(get_states(root))):
            print(',')
        else:
            print('\n};\n')

    
    print('bool final_states[' + str(len(get_states(root)) + 1) + '] = {')
    for i in range(len(get_states(root)) + 1):
        if (str(i) in get_final_states(root)):
            print('\t1', end='')
        else:
            print('\t0', end='')
        if (i != len(get_states(root))):
            print(',\t// {}'.format(i))
        else:
            print(f'\t// {i}\n}};\n')
    
    print('std::string tokens[{}] = {{'.format(len(get_states(root)) + 1))
    for state in root.iter('state'):
        if (int(state.get('id')) == 171):
            print('\t"{}",\t// {}'.format("", state.get('id')))
        elif (state.find('label') is not None):
            print('\t"{}",\t// {}'.format(state.find('label').text, state.get('id')))
        elif (state.find('final') is not None and state.find('label') is None and int(state.get('id')) > 1 and int(state.get('id')) < 144):
            print('\t"{}",\t// {}'.format("ID", state.get('id')))
        else:
            print('\t"ERRO",\t// {}'.format(state.get('id')))
    print('};')




# create a main function to test the get transitions function
if __name__ == '__main__':
    main()