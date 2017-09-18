/* Classe Main para testar a Coordenação */

import javax.swing.*;

public class Main{
    public static void main(String args[]){
        int c;
        Coordenacao bcc;
        bcc = new Coordenacao("Ciencia da Computacao");

        while(true){
            c = Integer.parseInt(JOptionPane.showInputDialog("Bem-vindo a Coordenacao do BCC.\n[1]. Cadastrar Aluno.\n[2]. Cadastrar Grade.\n[3]. Cadastrar Professor.\n[4]. Mostrar Alunos.\n[5]. Mostrar Grades.\n[6]. Mostrar Professores.\n[7]. Matricular Aluno.\n[8]. Atualizar Aluno.\n[9]. Matricular Professor.\n[10]. Desmatricular Professor.\n[0]. Sair\n"));
            if(c == 0) break;
            else if(c == 1) bcc.CadastrarAluno();
            else if(c == 2) bcc.CadastrarGrade();
            else if(c == 3) bcc.CadastrarProfessor();
            else if(c == 4) bcc.MostrarAlunos();
            else if(c == 5) bcc.MostrarGrades();
            else if(c == 6) bcc.MostrarProfessores();
            else if(c == 7) bcc.MatricularAluno();
            else if(c == 8) bcc.AtualizarAluno();
            else if(c == 9) bcc.MatricularProfessor();
            else if(c == 10) bcc.DesmatricularProfessor();
        } 
    }
}