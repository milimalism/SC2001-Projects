import pandas as pd
def insertionsort(list):
    print("hi, insertions sort")
    for i in range(1, len(list)):
        j = i
        while j > 0:
            if list[j] < list[j-1]:
                list[j], list[j-1] = list[j-1], list[j]
                j -= 1
            else:
                break
        i += 1
        print(i)

    print(list)

def writetoexcel():
    fullData = [['Array Size', 'Array', 'Key Comparisons', 'Time taken', 'S'], [900000, 0, 25526025, 8942850959, 100], [900000, 1, 25531570, 9029031417, 100], [900000, 2, 25513539, 9000756625, 100], [900000, 3, 25532511, 9064629458, 100], [900000, 4, 25536412, 9088633291, 100], [900000, 5, 25535568, 9186968458, 100], [900000, 6, 25516353, 9253174834, 100], [900000, 7, 25524781, 9228213209, 100], [900000, 8, 25535940, 9235382667, 100], [900000, 9, 25530047, 9200587208, 100]]
    new_data = pd.DataFrame(fullData[1:], columns=fullData[0])

    # Specify the Excel file name
    excel_file = "2001.xlsx"

    # Load the existing Excel file into a DataFrame
    existing_df = pd.read_excel(excel_file)

    # Append the new data to the existing DataFrame
    updated_df = existing_df.append(new_data, ignore_index=True)

    # Save the updated DataFrame back to the Excel file without overwriting
    updated_df.to_excel(excel_file, index=False)

writetoexcel()