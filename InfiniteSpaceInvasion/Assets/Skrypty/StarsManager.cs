using UnityEngine;
using System.Collections;

[RequireComponent (typeof(SpriteRenderer))]			// wymagany komponent: SpriteRenderer

public class StarsManager : MonoBehaviour {

	public int Offset = 2;							// przesunięcie decydujące kiedy dodajemy nowy obrazek
	public bool posiadaKlon = false;				// czy posiada skopiowane tło po prawej stronie

	public bool reverseScale = false;				// odwracanie tła

	float spriteWidth = 0f;							// szerokość Sprite'a
	Camera kamera;									// kamera
	Transform myTransform;							// transform tego obiektu


	void Awake()
	{
		kamera = Camera.main;
		myTransform = transform;
	}


	void Start () {
		SpriteRenderer sRenderer = GetComponent<SpriteRenderer>();
		spriteWidth = sRenderer.sprite.bounds.size.x;

		Invoke("killme",8);
	}


	void Update () {
		if(posiadaKlon == false){
			float camHorizontExtend = kamera.orthographicSize * Screen.width/Screen.height;
			float edgeVisiblePosition = (myTransform.position.x + spriteWidth) - camHorizontExtend;

			if(kamera.transform.position.x >= edgeVisiblePosition - Offset)
			{
				stworzTlo();
				posiadaKlon = true;
			}
		}
	}


	void stworzTlo()
	{
		Vector3 newPosition = new Vector3(myTransform.position.x + spriteWidth,myTransform.position.y,myTransform.position.z);
		Transform newTlo = Instantiate(myTransform,newPosition,myTransform.rotation) as Transform;

		if(reverseScale)
		{
			newTlo.localScale = new Vector3((newTlo.localScale.x * -1),1f,1f);
		}

		newTlo.parent = myTransform.parent;
	}

	void killme()
	{
		Destroy(this.gameObject);
	}
}
