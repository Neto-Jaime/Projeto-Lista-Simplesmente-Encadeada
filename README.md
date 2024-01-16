#Esse projeto foi para a disciplina de Estrutura de Dados feito por:Jaime Neto, Davi Vieira e Luiz.
#Projeto solicitado pelo professor Alexandre como parte avaliativa, no semestre do ano de 2023. Assim possamos por em prática o que foi aprendido.

#SITEMA DE CADATSRO DE CONSULTAS MÉDICAS.(Utilizando a linguagem C)

Nosso sistema consiste algumas modificações que ajustamos para melhor atender como:
1. Para ser cadastrado uma consulta para o paciente, deverá ser digitado um dia/mês válido.(só aceitará até o dia 31 e o mês 12).
2. Vale também para  horário, que está no formato de 24h.(horário válido é de 7h às 18h, somente as 12h não é possível pois implementei como se fosse horário de almoço)OBS: LEMBRANDO QUE RETIRAMOS OS MINUTOS POIS O SENHOR SOLICITOU.
3. O sistema identifica os CPF dos pacientes já cadastrados e caso use um nome diferente para um paciente já cadastrado com nome diferente ele emitirá erro.
4. O mesmo CPF de um paciente com uma consulta marcada para x dia, não pode marcar uma outra consulta naquele x dia, mesmo que seja horário e especialidade diferente.
5. Outro CPF diferente(paciente diferente) pode marcar uma consulta no mesmo dia e horário que um outro paciente, se caso seja para um médico (especialidade )(CRM) diferente, caso seja data, horário e CRM iguais será emitido erro. 
6. A lista é iniciada pela consulta mais recente.
7. Ultima implemntação que fiz foi utilizando arquivos, onde salvo toda a lista em arquivo do tipo binário. Toda vez que fecho a pagina de cadastro a lista é salva e assim toda vez que entro novamnte na pagina de cadastro a lista é carregada com as ultimas informações informações.
Bem como algumas outras implementações para que a lógica do sistema não se perca. Caso surja dúvida de alguma implementação dirigir -se a equipe.

Esse trabalho foi bastnte simples mas serviu para por em práticas os conceitos da disciplina, quaiquer sugestões será bem vinda.
Grato!.
