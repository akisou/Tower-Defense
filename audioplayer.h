#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H
#include <QMediaPlayer>
#include <QObject>



enum SoundType
{
	TowerPlaceSound,		// 放塔时的声音
	LifeLoseSound,			// 基地费血时的声音
    LaserShootSound,		// 打中敌人时的声音
	EnemyDestorySound		// 敌人升天时的声音
};

class AudioPlayer : public QObject
{
public:
	explicit AudioPlayer(QObject *parent = 0);

	void startBGM();
	void playSound(SoundType soundType);
    void changeVolumn(int value);

private:
	QMediaPlayer *m_backgroundMusic; // 只用来播放背景音乐
};


#endif // AUDIOPLAYER_H
