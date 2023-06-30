import pandas as pd
import pyodbc 

server = '192.168.10.99\WINCC' 
database = 'PROCESS_DATA' 
username = 'SA' 
password = 'sa' 
cnxn = pyodbc.connect('DRIVER={ODBC Driver 18 for SQL Server};SERVER='+server+';DATABASE='+database+';ENCRYPT=no;UID='+username+';PWD='+ password)

df = pd.read_sql_query("SELECT * FROM OEE", cnxn)

lista = pd.unique(df[['PEL_COD_1', 'PEL_COD_2', 'PEL_COD_3', 'PEL_COD_4', 'PEL_COD_5']].values.ravel('K')).tolist()
newlista = []

for cod in lista:
  if str(cod).startswith("6"):
    newlista.append(cod)

newlista.sort()

newlista.insert(0,"All")

df = pd.DataFrame(newlista, columns=['Codigos'])


df.to_excel('Lista_Codigos.xlsx', index=False)
