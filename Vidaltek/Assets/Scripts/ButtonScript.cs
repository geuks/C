using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DoozyUI;

public class ButtonScript : MonoBehaviour {

    public Button attachedButton;
    public Image attachedImage;

    void OnStart()
    {
        attachedImage = this.GetComponent<Image>();
    }
}
