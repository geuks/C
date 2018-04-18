using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using UnityEngine.EventSystems;

public class TwoArgs : MonoBehaviour
{
    private GameObject buttonGO;
    private Button button;
    private GameManager gm;
    private Button rightAnswerDescription, rightAnswerClasse;
    private Button[] descriptionsButtons = new Button[4], classesButtons = new Button[4];
    private Color falseAnswer = new Color(0.6f, 0f, 0f, 0.8f), trueAnswer = new Color(0f, 0.6f, 0f, 0.8f), initColorDescription,initColorClasse;
    private Image cadre1, cadre2;
    private ButtonScript bt;

    public void CustomClick(Image b)
    {
        buttonGO = EventSystem.current.currentSelectedGameObject;
        button = buttonGO.GetComponent<Button>();

        

        gm = this.GetComponent<GameManager>();
        descriptionsButtons = gm.descriptionsButton;
        classesButtons = gm.classesButton;
        rightAnswerClasse = gm.RightButtonClasse;
        rightAnswerDescription = gm.RightButtonDescription;

        initColorDescription = gm.initColorDescription;
        initColorClasse = gm.initColorClasse;

        CheckDescriptions(b);
        CheckClasses(b);

        gm.ClickTime++;
        if(gm.ClickTime == 2)
        {
            gm.ClickTime = 0;
            gm.StartCoroutine(gm.TransitionToNextQuestion());
            StartCoroutine(TransitionToNextQuestion());
        }
    }

    public IEnumerator TransitionToNextQuestion()
    {
        yield return new WaitForSeconds(gm.timeBetweenQuestions);
        InitGame();
    }

    public void InitGame()
    {
        foreach (Button x in descriptionsButtons)
        {
            x.image.color = initColorDescription;
            x.interactable = true;
        }
        foreach (Button x in classesButtons)
        {
            x.image.color = initColorClasse;
            x.interactable = true;
        }
        foreach(Image x in gm.allCadre)
        {
            x.enabled = false;
        }
    }

    private void CheckDescriptions(Image b)
    {
        if ((rightAnswerDescription == button) && (button.tag == "Description"))
        {
            button.image.color = trueAnswer;
            b.enabled = true;


            foreach (Button x in descriptionsButtons)
            {
                if (x != button)
                    x.image.color = falseAnswer;
                x.interactable = false;
            }
        }
        else if (button.tag == "Description")
        {
            rightAnswerDescription.image.color = trueAnswer;
            rightAnswerDescription.image.enabled = true;
            b.enabled = true;

            foreach (Button x in descriptionsButtons)
            {
                if (x != rightAnswerDescription)
                    x.image.color = falseAnswer;
                x.interactable = false;
            }
        }
    }

    private void CheckClasses(Image b)
    {
        if ((rightAnswerClasse == button) && (button.tag == "Classe"))
        {
            button.image.color = trueAnswer;
            b.enabled = true;


            foreach (Button x in classesButtons)
            {
                if (x != button)
                    x.image.color = falseAnswer;
                x.interactable = false;
            }
        }
        else if (button.tag == "Classe")
        {
            rightAnswerClasse.image.color = trueAnswer;
            rightAnswerClasse.image.enabled = true;
            b.enabled = true;

            foreach (Button x in classesButtons)
            {
                if (x != rightAnswerClasse)
                    x.image.color = falseAnswer;
                x.interactable = false;
            }
        }
    }
}