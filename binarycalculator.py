# Function to compute one's complement
def first_complement(binary1):
    result = ""
    # Loop through each bit in the binary number
    for i in range(len(binary1)):
        # Toggle each bit: '0' becomes '1' and '1' becomes '0'
        if binary1[i] == '0':
            result += '1'
        else:
            result += '0'
    return result





# Function to compute two's complement
def second_complement(binary1):
    result = ''
    result2 = ''
    counter = len(binary1) - 1
    count_ones = 0
    # Iterate through the binary number from right to left
    while counter >= 0:
        # Handling '0' bits
        if binary1[counter] == '0':
            if count_ones == 0:
                result += '0'
            elif count_ones >= 1:
                result += '1'
        # Handling '1' bits
        elif binary1[counter] == '1':
            if count_ones == 0:
                result += '1'
            elif count_ones >= 1:
                result += '0'
            count_ones += 1
        counter -= 1
    # Reverse the result to get the two's complement
    for i in range(len(result)):
        result2 += result[len(result) - 1 - i]
    return result2






# Function to check if a string is a valid binary number
def is_binary(binary_str):
    return all(bit in '01' for bit in binary_str)




# Function to perform binary addition
def addition(binary1,binary2):
    # Check if the second input is a valid binary number
    if not is_binary(binary2):
        print("Please insert a valid binary number.")
        return
    max1 = max(len(binary1),len(binary2))
    binary1 = binary1.zfill(max1)
    binary2 = binary2.zfill(max1)
    # the reversed binary sum
    binary_sum1 = ''
    #the forward sum
    binary_sum2 = ''
    carry = 0
    for i in range(max1):
        if carry == 0:
            if int(binary1[max1-1-i]) == 0 or int(binary2[max1-1-i]) == 0:
                binary_sum1+=str(int(binary1[max1-1-i]) + int(binary2[max1-1-i]))
            if int(binary1[max1-1-i]) ==  1 and int(binary2[max1-1-i]) == 1:
                binary_sum1+=str(0)
                carry += 1
        elif carry == 1:
            if int(binary1[max1-1-i]) == 0 and int(binary2[max1-1-i]) == 0:
                binary_sum1+=str(1)
                carry = 0
            if int(binary1[max1-1-i]) == 1 and int(binary2[max1-1-i]) == 0:
                binary_sum1+=str(0)
            if int(binary1[max1-1-i]) == 0 and int(binary2[max1-1-i]) == 1:
                binary_sum1+=str(0)
            if int(binary1[max1-1-i]) == 1 and int(binary2[max1-1-i]) == 1:
                binary_sum1+=str(1)
    if carry == 1:
        binary_sum1+=str(carry)
    for i in range(len(binary_sum1)):
        binary_sum2+=binary_sum1[len(binary_sum1)-1-i]

    return binary_sum2





# Function to perform binary subtraction
def subtraction(binary1,binary2):
    # Check if the second input is a valid binary number
    if not is_binary(binary2):
        print("Please insert a valid binary number.")
        return
    # Make sure the binary strings have the same length
    len_diff = len(binary1) - len(binary2)
    if len_diff > 0:
        binary2 = '0' * len_diff + binary2
    elif len_diff < 0:
        binary1 = '0' * abs(len_diff) + binary1

    result = ''
    borrow = 0

    # Iterate through the binary strings from right to left
    for i in range(len(binary1) - 1, -1, -1):
        bit1 = int(binary1[i])
        bit2 = int(binary2[i])

        # Perform binary subtraction with borrow
        temp_result = bit1 - bit2 - borrow

        if temp_result < 0:
            temp_result += 2
            borrow = 1
        else:
            borrow = 0
        result = str(temp_result) + result

    # Remove leading zeros by finding the first '1'
    first_one_index = next((i for i, bit in enumerate(result) if bit == '1'), None)
    result = result[first_one_index:] if first_one_index is not None else '0'
    if result == '':
        return 0
    else:
        return result




# Main program in loop
while True:
    print("\n**binary calculator**")
    print("A) Insert new numbers")
    print("B) Exit")
    choice1 = input("Enter your choice (A/B): ").upper()
    if choice1 == 'B':
        break
    elif choice1 == 'A':
        binary1 = str(input("Please insert the first number: "))
        # Check if the input is a valid binary number
        if not is_binary(binary1):
            print("Please insert a valid binary number.")
            continue
        print("\n** please select the operation **")
        print("A) Compute one's complement")
        print("B) Compute two's complement")
        print("C) Addition")
        print("D) Subtraction")
        choice2 = input("Please enter your choice (A/B/C/D): ").upper()
        # Perform the selected operation
        if choice2 == 'A':
            print(first_complement(binary1))
        if choice2 == 'B':
            print(second_complement(binary1))
        if choice2 == 'C':
            binary2 = input("Please insert the second number: ")
            print(addition(binary1,binary2))
        if choice2 == 'D':
            binary2 = input("Please insert the second number: ")
            print(subtraction(binary1,binary2))
        if choice2 != 'A' and choice2 != 'B' and choice2 != 'C' and choice2 != 'D':
            print("Please select a valid operation.")
            continue
    elif choice1 != 'A' and choice1 != 'B':
        print("Please select a valid choice.")
