using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using MaterialUI;
using TMPro;

public class GameManager : MonoBehaviour {

    private TwoArgs ta;
    public TMP_Text randomWord;
    public Text[] descriptions = new Text[4],classes = new Text[4];
    public Button[] descriptionsButton = new Button[4], classesButton = new Button[4];
    [SerializeField]
    public TextAsset myText;
    public Structure st;
    public Structure.Row[] myList;
    private string[] myStringText;
    private int nbr=1,count=0,i;
    private int randomAnswer;
    [SerializeField]
    private int[] randomFalseAnswer = new int[3];
    private int cpt = 0;
    public string RightAnswerDescription,RightAnswerClasse;
    public Button RightButtonDescription, RightButtonClasse;
    public string DescriptionSelected,ClasseSelected;
    public float timeBetweenQuestions = 2f;
    public int ClickTime = 0;
    public Color initColorDescription, initColorClasse;
    public Image[] allCadre = new Image[8];

    public IEnumerator TransitionToNextQuestion()
    {
        yield return new WaitForSeconds(timeBetweenQuestions);
        LaunchGame();
    }

    bool IsSameText()
    {
        int i = 0, j = 0;

        for (i = 0; i < randomFalseAnswer.Length; i++)
        {
            for (j = 0; j < randomFalseAnswer.Length; j++)
            {
                if ((myList[randomFalseAnswer[i]].Description==myList[randomFalseAnswer[j]].Description) && (i!=j) || (myList[randomAnswer].Description != myList[randomFalseAnswer[i]].Description))
                    if ((myList[randomFalseAnswer[i]].Classe == myList[randomFalseAnswer[j]].Classe) && (i != j) || (myList[randomAnswer].Classe != myList[randomFalseAnswer[i]].Classe))
                        return true;
            }
        }

        return false;
    }

    bool IsSame(int[] x)
    {
        int i = 0, j = 0;

        for (i = 0; i < x.Length; i++)
        {
            for (j = 0; j < x.Length; j++)
            {
                if ((x[i] == x[j]) && (i != j) || randomAnswer == x[i])
                    return true;
            }
        }
        return false;
    }

    int[] Get3RandomNotSame()
    {
        int[] x = new int[3];
        int i = 0;

        while (IsSame(x) && IsSameText())
        {
            for (i = 0; i < x.Length; i++)
            {
                x[i] = Random.Range(0, myList.Length);
            }
        }
            
        return x;
    }

    

    public void LaunchGame()
    {
        cpt = 0;
        randomAnswer = Random.Range(0, myList.Length);
        randomWord.text = st.GetNomfromRow(myList[randomAnswer]);

        randomFalseAnswer = Get3RandomNotSame();

        nbr = Random.Range(0, 3);


        for (i = 0; i < randomFalseAnswer.Length + 1; i++)
        {
            if (i == nbr)
            {
                classes[nbr].text = st.GetClassefromRow(myList[randomAnswer]);
            }
            else
            {
                classes[i].text = st.GetClassefromRow(myList[randomFalseAnswer[cpt]]);
                cpt++;
            }

        }
        RightAnswerClasse = classes[nbr].text;
        RightButtonClasse = classesButton[nbr];
        cpt = 0;
        nbr = Random.Range(0, 3);
        randomFalseAnswer = Get3RandomNotSame();

        for (i = 0; i < randomFalseAnswer.Length + 1; i++)
        {
            if (i == nbr)
            {
                descriptions[nbr].text = st.GetDescriptionfromRow(myList[randomAnswer]);
            }
            else
            {
                descriptions[i].text = st.GetDescriptionfromRow(myList[randomFalseAnswer[cpt]]);
                cpt++;
            }

        }
        RightAnswerDescription = descriptions[nbr].text;
        RightButtonDescription = descriptionsButton[nbr];
    }
    void OnEnable()
    {
        SceneManager.sceneLoaded += OnSceneLoaded;
    }

    void OnDisable()
    {
        SceneManager.sceneLoaded -= OnSceneLoaded;
    }


    private void OnSceneLoaded(Scene scene, LoadSceneMode mode)
    {
        myStringText = myText.text.Split('\n', ',');
        myList = new Structure.Row[(myStringText.Length) / 4];
        st = new Structure { };
        

        if (myList != null)
        {
            for(i=0;i< (myStringText.Length) / 4;i++)
            {
                myList[i] = new Structure.Row {};
            }
            

            for (i = 0; i < myStringText.Length; i++)
            {

                switch (nbr)
                {
                    case 1:
                        myList[count].Id = myStringText[i];
                        break;

                    case 2:
                        myList[count].Nom = myStringText[i];
                        break;

                    case 3:
                        myList[count].Classe = myStringText[i];
                        break;

                    case 4:
                        myList[count].Description = myStringText[i];
                        break;
                    default:
                        break;

                }

                nbr = nbr + 1;

                if (nbr == 5)
                {
                    nbr = 1;
                    count++;
                }
            }
        }
        LaunchGame();
    }

}
