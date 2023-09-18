// Include important C++ libraries here
#include <sstream>
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<unordered_map>
#include<string>
#include<math.h>


using namespace sf;
using namespace std;



int main()
{

    // Creating the scene
    
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Buzzy's Revenge!", Style::Default);

	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");

	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    sf::Text titleText;
	sf::Text messageText[4];
	sf::Text scoreText;
	sf:: Text powerBar;
    sf:: Text livesText;
    sf:: Text createdByText;

	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
    titleText.setFont(font);
	scoreText.setFont(font);
	powerBar.setFont(font);
    livesText.setFont(font);
    createdByText.setFont(font);
	bool soundPlayed = false;
	// Assign the actual message
	titleText.setString("Buzzy's Revenge");
	messageText[0].setString("Press Enter to Restart Game");
	messageText[1].setString("\nPress Escape to exit");
	messageText[2].setString("\nPress Space to Power Up");
	messageText[3].setString("\nPress up/down arrow to aim");
    
	scoreText.setString("Score: 99");
    powerBar.setString("Power ");
    livesText.setString("Lives ");
    createdByText.setString("\n\nCreated By:\nNoaima Bari");

	for(int i=0; i<4; i++)
	{
        messageText[i].setFont(font);
		messageText[i].setCharacterSize(50);
		messageText[i].setFillColor(Color::White);
        FloatRect textRect = messageText[i].getLocalBounds();
		messageText[i].setOrigin(textRect.left +
			textRect.width / 2.0f,
			textRect.top +
			textRect.height / 2.0f);
		messageText[i].setPosition(1920 / 2.0f, 1080 / 2.0f - (3-i)*50);

	}
	bool drawUnicorn = true;
	titleText.setCharacterSize(65);
	scoreText.setCharacterSize(30);
    powerBar.setCharacterSize(25);
    livesText.setCharacterSize(25);

	// Choose a color
	titleText.setFillColor(Color::Red);
	scoreText.setFillColor(Color::White);
    powerBar.setFillColor(Color::White);
	
    // Making title bold
	titleText.setStyle(sf::Text::Bold);

	// Position the text
    FloatRect textRect = titleText.getLocalBounds();
	
	titleText.setOrigin(textRect.left +
			textRect.width / 2.0f,
			textRect.top +
			textRect.height / 2.0f);

	titleText.setPosition(1920 / 2.0f, 1080 / 2.0f - 300);
	scoreText.setPosition(1700, 0);
    powerBar.setPosition(40, 900);
    livesText.setPosition(10, 30);

    
    createdByText.setCharacterSize(25);
    createdByText.setFillColor(Color::White);
    FloatRect CRect = createdByText.getLocalBounds();
	createdByText.setOrigin(CRect.left +
			CRect.width / 2.0f,
			CRect.top +
			CRect.height / 2.0f);
            
	createdByText.setPosition(1920 / 2.0f, 1080 - 400);

    bool gameOver = false;
	Text gameOverText;
	gameOverText.setString("GAME OVER!");
	gameOverText.setFont(font);
	FloatRect GRect = createdByText.getLocalBounds();
	gameOverText.setOrigin(GRect.left +
			GRect.width / 2.0f,
			GRect.top +
			GRect.height / 2.0f);
            
	gameOverText.setPosition(1920 / 2.0f - 100, 1080 / 2.0f - 300);
	gameOverText.setCharacterSize(75);
	gameOverText.setFillColor(Color::Red);


	// Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/insect.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(1500, 100);
    spriteBee.scale(sf::Vector2f(1.5f, 1.5f));


	//bool beeActive = false;
	float beeSpeedX = 0.1f, beeSpeedY = 0.1f;

    // Prepare the buzzy lives
    Texture buzzLife;
    buzzLife.loadFromFile("graphics/buzzy life.png");
    Sprite lives[5];
    for(int i=0; i<5; i++)
	{
        lives[i].setTexture(buzzLife);
        lives[i].setPosition(90 + 60*i, 20);
        lives[i].scale(sf::Vector2f(0.5f, 0.5f));

    }

    // Preparing the buzz
    Texture buzz_texture;
    buzz_texture.loadFromFile("graphics/smallbuzzy.png");
    Sprite buzz;
	int num_lives = 5;
    buzz.setTexture(buzz_texture);
    buzz.scale(sf::Vector2f(1.15f, 1.15f));
	float xInitial = 50, yInitial = 600, rotate_initial = buzz.getRotation()-20;
    buzz.setPosition(50, 600);
    // rotate the buzz
    buzz.setRotation(rotate_initial);

	int eStart = 0, eEnd = 10;
    // Preparing the entities
    Texture entities[10];
    entities[0].loadFromFile("graphics/sheep.png");
    entities[1].loadFromFile("graphics/bunny.png");
    entities[2].loadFromFile("graphics/dog.png");
    entities[3].loadFromFile("graphics/tiger.png");
    entities[4].loadFromFile("graphics/mouse.png");
    entities[8].loadFromFile("graphics/angry_unicorn.png");
    entities[6].loadFromFile("graphics/frog.png");
    entities[7].loadFromFile("graphics/Georgia_Bulldogs_logo_dog_g.png");
    entities[5].loadFromFile("graphics/pig.png");
    entities[9].loadFromFile("graphics/chicken.png");
    Sprite characters[10];
	bool drawBee = true;
    for(int i=0; i<10; i++)
	{
        characters[i].setTexture(entities[i]);
    }

    characters[3].scale(sf::Vector2f(0.1f, 0.1f));
	
    for(int i=0; i<5; i++)
	{
        characters[i].setPosition(1650, 950 - (5-i)*100);

    }
    for(int i=5; i<10; i++)
	{
        characters[i].setPosition(1790-(10-i), 950 - ((10-i)*100));
    }

	
	

	// Variables to control time itself
	Clock clock1;
	Clock clock2;
	float xC, yC;
	// Power bar
	RectangleShape timeBar;
	float timeBarWidth = 0;
	float timeBarHeight = 50;
	timeBar.setSize(Vector2f(timeBarWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition(150, 950 - timeBarHeight);

	float timeBarWidthPerSecond = 400 / 5;

	// Track whether the game is running
	bool paused = true;
	// Draw some text
	int score = 0;

	bool flyBuzzy = false, hitTiger = false, hitBullDog = false, hitBee = false, hitUnicorn = false;
	float rotationAngle = 0;

	/*
	v*cos(theta) * t = 1920
	max v = 1920/cos(theta)*1;
	min v = 1920/cos(theta)*4;
	*/
	float buzzVelocity, sn = -1;
	float buzzXVelocity = 0, buzzYVelocityInitial = 0, buzzYVelocityNew = 0;
	float angleOfProjection = buzz.getRotation(), buzzXPosition = 50, buzzYPosition = 600;
	buzzVelocity = 0;
	float dt = 0;
	bool levelRecreate = false;
	bool started_again = false;

	SoundBuffer gameOverBuffer; 
	gameOverBuffer.loadFromFile("sound/out_of_time.wav");
	Sound gameOverSound;
	gameOverSound.setBuffer(gameOverBuffer);
	
	while (window.isOpen())
	{
	
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		sf::Event event;
		while (window.pollEvent(event))
		{
    		if (event.type == sf::Event::Closed) 
			{
        		window.close();
    		}

			if (event.type == sf::Event::KeyReleased)
			{
    			if (event.key.code == sf::Keyboard::Space)
    			{
					Time dt = clock1.restart();
					flyBuzzy = true;
					//num_lives--;
    			}
			}			
		
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Start the game when ENTER is pressed 

		if(Keyboard::isKeyPressed(Keyboard::Return))
		{	
			paused = false;
			score = 0;
			Time t = clock2.restart();
			scoreText.setString("Score: 0");
        }

		
		if (!paused)
		{
			if(num_lives <= 0 && (buzz.getPosition().x < 0 || buzz.getPosition().y > 1080 || buzz.getPosition().x > 1920 || buzz.getPosition().y < 0))
			{
				gameOver = true;
			}
			
			// Random movement of the bee
			
			float dt = clock2.getElapsedTime().asSeconds();

			if(spriteBee.getPosition().x < 0 || spriteBee.getPosition().y > 1080 || spriteBee.getPosition().x > 1920 || spriteBee.getPosition().y < 0)
			{
				
				sn*=-1;		// change direction
				srand(time(NULL));		// generating a random seed;
				beeSpeedX = rand()%10 * 0.005;	// generates random velocity between 0.01 and 0.09
				srand((int)time(0) * 20);
				beeSpeedY = rand()%10 * 0.005;
				srand(time(NULL));
				xC = rand()%1920;
				srand((int)time(0) * 50);
				yC = rand()%1080;
				spriteBee.setPosition(xC, yC);
			}
			spriteBee.setPosition(spriteBee.getPosition().x + sn * (beeSpeedX * dt),spriteBee.getPosition().y - sn * (beeSpeedY * dt));

			

			if(!flyBuzzy)
			{

				// set the buzz position

				buzz.setPosition(50, 600);
				if(started_again)
				{
					buzz.setRotation(rotate_initial);
					if(hitUnicorn == false && hitTiger == false && hitBullDog == false && hitBee == false)
					{
						num_lives--;
					}

					hitBullDog = false, hitTiger = false, hitBee = false, hitUnicorn = false;
					buzzXVelocity = 0, buzzYVelocityInitial = 0, buzzVelocity = 0;
					timeBarWidth = 0;
					started_again = false;
				}
				if(levelRecreate == true)
				{
					// change positions of evil mascots
					srand(time(NULL));
					drawBee = true;
					int r = rand()%5;
					float x1 = characters[3].getPosition().x;
					float y1 = characters[3].getPosition().y;
					float x2 = characters[r].getPosition().x;
					float y2 = characters[r].getPosition().y;
					characters[3].setPosition(x2, y2);
					characters[r].setPosition(x1, y1);
					srand(time(NULL));
					int r1 = 5 + rand()%4;
					float x3 = characters[7].getPosition().x;
					float y3 = characters[7].getPosition().y;
					float x4 = characters[r1].getPosition().x;
					float y4 = characters[r1].getPosition().y;
					characters[7].setPosition(x4, y4);
					characters[r1].setPosition(x3, y3);
					drawUnicorn = true;
					eStart = 0;
					eEnd = 10;
					hitBullDog = false, hitTiger = false, hitBee = false, hitUnicorn = false;
					// set number of lives to 5
					num_lives = 5;
					levelRecreate = false;
				}

				// First handle pressing the right cursor key
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					buzzXVelocity = 0, buzzYVelocityInitial = 0, buzzVelocity = 0;
					timeBarWidth = 0;
					rotationAngle = buzz.getRotation() + 0.1;
					buzz.setRotation(rotationAngle); // rotate buzzy down

				}	

				// Handle the left cursor key
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					rotationAngle = buzz.getRotation() - 0.1;
					buzz.setRotation(rotationAngle);
			
				}

				// screen width = 29 cm = 0.29 m
				angleOfProjection = rotationAngle * 3.14 / 180;	// angle of projection in radians
				/*
				minV = 0.29/(cos(angleOfProjection) * 4); // to cover the screen in 4 sec
				maxV = 0.29/(cos(angleOfProjection) * 1);	// to cover the screen in 1 sec
				buzzVelocity = minV;
				buzzXVelocity = minV*cos(angleOfProjection);
				buzzYVelocityInitial = -1 * minV*sin(angleOfProjection);
				//cout<<minV<<" "<<maxV<<endl;
				*/
				if (Keyboard::isKeyPressed(Keyboard::Space) && buzzXVelocity <= 0.29)
				{
						// increase width of power bar and increase buzz velocity 

						buzzVelocity += 0.0001;
						//cout<<"buzzVelocity"<<endl;
						buzzXVelocity = buzzVelocity * cos(angleOfProjection);
						buzzYVelocityInitial = buzzVelocity * sin(angleOfProjection);
						//cout<<"X Velocity"<<buzzXVelocity<<"Y Velocity"<<buzzYVelocityInitial<<endl;
						timeBarWidth = (buzzXVelocity/(0.29))*400;
						timeBar.setSize(Vector2f(timeBarWidth, timeBarHeight));
					
				}


			} // end if(!acceptInput)

			else if(flyBuzzy)
			{
				
				// if both tiger and bull dog are hit level is recreated
				if(hitTiger == true && hitBullDog == true)
				{
					levelRecreate = true;
					flyBuzzy = false;
				}
				
				// Checking if buzzy hit the tiger
				if(/*hitTiger == false && */(abs(buzz.getPosition().x - characters[3].getPosition().x) < 5 && abs(buzz.getPosition().y - characters[3].getPosition().y) < 5))
				{
					eStart += 5;
					flyBuzzy = false;
					//started_again = true;
					hitTiger = true;
					score += 25;
					std::stringstream ss;	// modern object oriented way of creating a string stream
					ss << "Score:" << score ;
					scoreText.setString(ss.str()); // you can call str to get an instance of the string that has been created
				}

				// checking if buzzy hit the mad unicorn

				if((drawUnicorn == true) && (hitUnicorn == false) && (abs(buzz.getPosition().x - characters[8].getPosition().x) < 10 && abs(buzz.getPosition().y - characters[8].getPosition().y) < 10))
				{
					
					hitUnicorn = true;
					drawUnicorn = false;
					flyBuzzy = false;
					started_again = true;
					
					if(num_lives<5)
					{
						num_lives+=1; // + 2 to account for 1 extra life and 1 lost life due to pressing space
					}
				}
				// checking if buzzy hit the bulldog
				if(/*hitBullDog == false && */ (abs(buzz.getPosition().x - characters[7].getPosition().x) < 10 && abs(buzz.getPosition().y - characters[7].getPosition().y) < 10))
				//if(hitBullDog == false && characters[7].getOrigin())
				{
					eEnd -= 5;
					flyBuzzy = false;
					//started_again = true;
					hitBullDog = true;
					score += 25;
					std::stringstream ss;	// modern object oriented way of creating a string stream
					ss << "Score:" << score ;
					scoreText.setString(ss.str()); // you can call str to get an instance of the string that has been created
				}
				
				// checking if buzzy hit the bee
				if((drawBee == true) && (hitBee == false) && (abs(buzz.getPosition().x - spriteBee.getPosition().x) < 10 && abs(buzz.getPosition().y - spriteBee.getPosition().y) < 10))
				{
					
					hitBee = true;
					drawBee = false;
					score += 75;
					std::stringstream ss;	// modern object oriented way of creating a string stream
					ss << "Score:" << score ;
					scoreText.setString(ss.str()); // you can call str to get an instance of the string that has been created
				}
				
				
				// Projectile Motion of Buzzy
				if((buzz.getPosition().x <= 1920) && (buzz.getPosition().y >= 0))
				{
					float time_elapsed = clock1.getElapsedTime().asSeconds();
					buzzXPosition = xInitial + (buzzXVelocity * time_elapsed * 1920/0.29);
					buzzYPosition = yInitial + ((buzzYVelocityInitial * time_elapsed)*1080/0.165)  + (0.5*98*time_elapsed*time_elapsed);
					buzz.setPosition(buzzXPosition, buzzYPosition);
					buzz.setRotation(buzz.getRotation() + 0.02);
				}
				
				if(buzz.getPosition().x < 0 || buzz.getPosition().y < 0 || buzz.getPosition().x > 1920 || buzz.getPosition().y > 1080)
				{
					flyBuzzy = false;
					started_again = true;
				}	

				if(eStart>=eEnd)
				{
					levelRecreate = true;
					flyBuzzy = false;
					started_again = true;
				}	

			}

			
			
			

		}
		

		
		
		/*
		****************************************
		Update the scene
		****************************************
		*/
		
		 /*
		 ****************************************
		 Draw the scene
		 ****************************************
		 */

		 // Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the bee
		if(drawBee)
		{
			window.draw(spriteBee);

		}

		// Draw the score
		window.draw(scoreText);

        // Draw the Power bar text
        window.draw(powerBar);

		// Draw the powerbar
		window.draw(timeBar);

        // Draw lives
        window.draw(livesText);

		 for(int i=0; i<num_lives; i++)
		{
            window.draw(lives[i]);
        }
		
		if(hitUnicorn == true)
		{
			// drop all images above it by 1
			// mad unicorn at 8
			for(int i=5; i<=7; i++)
			{	
				characters[i].setPosition(characters[i+1].getPosition());
			}
		}

		if(drawUnicorn == true && eEnd == 10)
		{
			window.draw(characters[8]);
		}
        for(int i=eStart; i<eEnd; i++)
		{
			if(i!=8)
			{
				window.draw(characters[i]);

			}

		}

        window.draw(buzz);

		if (paused)
		{
			// Draw our message
			for(int i=0; i<4; i++)
			{
				window.draw(messageText[i]);

			}
			window.draw(titleText);
			window.draw(createdByText);
		}

		if(gameOver)
		{
			window.draw(gameOverText);
			if(soundPlayed == false){
				gameOverSound.play();
				soundPlayed = true;
			}
			
		}

		// Show everything we just drew
		window.display();


	}

	return 0;
}







