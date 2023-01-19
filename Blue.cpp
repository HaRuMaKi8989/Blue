#include "stdafx.h"
#include "Blue.h"
#include "Player.h"
//CollisionObjectを使用するために、ファイルをインクルードする。
#include "collision/CollisionObject.h"

Blue::Blue()
{
	characterController.Init(30.0f, 5.0f, position);
	//モデルを読み込む
	modelRender.Init("Assets/modelData/Blue.tkm");
	//プレイヤーのオブジェクトを引っ張ってくる
	player = FindGO<Player>("player");
	//SetScaleは大きさを変える
	modelRender.SetScale(3.0f,3.0f,3.0f);

	//プレイヤーが作成した、レバー用のコリジョンの配列を取得。
const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_Blue");

	//for文で配列を回す。
	for (auto collision : collisions)
	{
		//レバー自身のコリジョンとプレイヤーのコリジョンが。
	//衝突していたら。
		if (collision->IsHit(collisionObject) == true)
		{
			//押すステートに遷移させる。
			m_BlueState = enBlueState_Push;

			//効果音を流す。
			/*SoundSource* se = NewGO<SoundSource>(0);
			se->Init(6);
			se->Play(false);
			se->SetVolume(0.6f);*/
		}
	}
	
	CollisionObject* collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = position;
	//球状のコリジョンを作成する。
	collisionObject->CreateSphere(collisionPosition, //座標。
		Quaternion::Identity, //回転。
		30.0f); //球の大きさ(半径)。
	collisionObject->SetName("player_Blue");

	physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	
	
}

Blue::~Blue()
{
	//コリジョンオブジェクトを削除する
	DeleteGO(collisionObject);
}


void Blue::ProcessTransitionPullState()
{
	//プレイヤーが作成した、レバー用のコリジョンの配列を取得。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_Blue");

	//for文で配列を回す。
	for (auto collision : collisions)
	{
		//レバー自身のコリジョンとプレイヤーのコリジョンが。
	//衝突していたら。
		if (collision->IsHit(collisionObject) == true)
		{
			//引くステートに遷移させる。
			m_BlueState = enBlueState_Pull;

			//効果音を流す。
			/*SoundSource* se = NewGO<SoundSource>(0);
			se->Init(6);
			se->Play(false);
			se->SetVolume(0.6f);*/
		}
	}
}


void Blue::Update()
{
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	m_moveSpeed.x = 5.0f;
	m_moveSpeed.z = 5.0f;


	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0f;

	/*forward.x = 0.0f;
	right.x = 0.0f;*/

	right *= stickL.x * 30.0f;
	forward *= stickL.y * 30.0f;

	moveSpeed += right + forward;


	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (hata == false) {
			hata = true;
		}
		else if(hata == true){
			{
				hata = false;
			}
		}
	}
	if (hata == true) {


		if (stickL.x != 0.0f || stickL.y != 0.0f) {
			QueRot.x = stickL.x;
			QueRot.z = stickL.y;
		}

		QueRot.Normalize();

		position.x += QueRot.x * m_moveSpeed.x;
		position.y += QueRot.y * m_moveSpeed.y;
		position.z += QueRot.z * m_moveSpeed.z;

		//回転を加算する
		rot.AddRotationDegY(0.0f);
		//絵描きさんに回転を教える
		modelRender.SetRotation(rot);

		//絵描きさんに座標を教える
		modelRender.SetPosition(position);
		//絵描きさんの更新処理
		modelRender.Update();

		position = characterController.Execute(moveSpeed, 1.0f / 60.0f);

		//moveSpeed += right + forward;

		//m_modelRender.SetPosition(position);
		/*colli = NewGO<CollisionObject>(0);

		colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 50.0f);

		colli->SetName("Blue");

		colli->SetPosition(position);*/

		//コリジョンオブジェクト作成
		

		//名前を付ける。
		//collisionObject->SetName("Player_Object");

		
	}
	

}

void Blue::Render(RenderContext& renderContext)
{
	//敵を描画する
	modelRender.Draw(renderContext);
}