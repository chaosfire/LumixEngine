#pragma once


#include <QDockWidget>


class MainWindow;


namespace Lumix
{
	class WorldEditor;
	class PipelineInstance;
}

namespace Ui
{
	class GameView;
}

class GameView : public QDockWidget
{
	Q_OBJECT

public:
	explicit GameView(MainWindow& parent);
	virtual ~GameView();

	QWidget* getContentWidget() const;
	void setWorldEditor(Lumix::WorldEditor& editor);
	void render();
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void keyPressEvent(QKeyEvent* event) override;

private slots:
	void on_playButton_clicked();

private:
	virtual void resizeEvent(QResizeEvent*) override;

private:
	Ui::GameView* m_ui;
	Lumix::WorldEditor* m_editor;
	MainWindow& m_main_window;
	class WGLRenderDevice* m_render_device;
};
