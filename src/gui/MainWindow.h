/*
 * MidiEditor
 * Copyright (C) 2010  Markus Schwenk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QCloseEvent>
#include <QMainWindow>
#include <QScrollBar>
#include <QSettings>
#include <QStringList>

class MatrixWidget;
class MidiEvent;
class MidiFile;
class ChannelListWidget;
class ProtocolWidget;
class EventWidget;
class ClickButton;
class QTabWidget;
class QMenu;
class TrackListWidget;
class QComboBox;
class MiscWidget;
class QGridLayout;
class MidiTrack;
class QShowEvent;
class Update;
class SelectionNavigator;
class TweakTarget;

#include "ToolbarActionInfo.h"

class MainWindow : public QMainWindow {

    Q_OBJECT

  public:
    MainWindow(QString initFile = "");
    void setFile(MidiFile* f);
    MidiFile* getFile();
    MatrixWidget* matrixWidget();
    EventWidget* eventWidget();
    void setStartDir(QString dir);
    void setInitFile(const char* file);
    bool saveBeforeClose();

  protected:
    void dropEvent(QDropEvent* ev);
    void dragEnterEvent(QDragEnterEvent* ev);

  public slots:
    void updateAll();
    void loadInitFile();
    void matrixSizeChanged(int maxScrollTime, int maxScrollLine, int vX, int vY);
    void play();
    void playStop();
    void stop(bool autoConfirmRecord = false, bool addEvents = true, bool resetPause = true);
    void pause();
    void forward();
    void back();
    void backToBegin();
    void forwardMarker();
    void backMarker();
    void load();
    void loadFile(QString file);
    void openFile(QString filePath);
    void save();
    void saveas();
    void undo();
    void redo();
    void muteAllChannels();
    void unmuteAllChannels();
    void allChannelsVisible();
    void allChannelsInvisible();
    void muteAllTracks();
    void unmuteAllTracks();
    void allTracksVisible();
    void allTracksInvisible();
    void about();
    void setFileLengthMs();
    void scrollPositionsChanged(int startMs, int maxMs, int startLine,
                                int maxLine);
    void record();
    void newFile();
    void panic();
    void screenLockPressed(bool enable);
    void scaleSelection();
    void alignLeft();
    void alignRight();
    void equalize();
    void glueSelection();
    void glueSelectionAllChannels();
    void deleteOverlaps();
    void resetView();
    void deleteSelectedEvents();
    void deleteChannel(QAction* action);
    void moveSelectedEventsToChannel(QAction* action);
    void moveSelectedEventsToTrack(QAction* action);
    void updateRecentPathsList();
    void openRecent(QAction* action);
    void updateChannelMenu();
    void updateTrackMenu();
    void muteChannel(QAction* action);
    void soloChannel(QAction* action);
    void viewChannel(QAction* action);
    void instrumentChannel(QAction* action);

    void renameTrackMenuClicked(QAction* action);
    void removeTrackMenuClicked(QAction* action);
    void showEventWidget(bool show);
    void showTrackMenuClicked(QAction* action);
    void muteTrackMenuClicked(QAction* action);

    void renameTrack(int tracknumber);
    void removeTrack(int tracknumber);

    void setInstrumentForChannel(int i);
    void spreadSelection();
    void copy();
    void paste();

    void addTrack();

    void selectAll();

    void transposeNSemitones();

    void markEdited();

    void colorsByChannel();
    void colorsByTrack();

    void editChannel(int i, bool assign = true);
    void editTrack(int i, bool assign = true);
    void editTrackAndChannel(MidiTrack* track);

    void manual();

    void changeMiscMode(int mode);
    void selectModeChanged(QAction* action);

    void pasteToChannel(QAction* action);
    void pasteToTrack(QAction* action);

    void selectAllFromChannel(QAction* action);
    void selectAllFromTrack(QAction* action);

    void divChanged(QAction* action);
    void quantizationChanged(QAction*);

    void enableMagnet(bool enable);

    void openConfig();

    void enableMetronome(bool enable);
    void enableThru(bool enable);

    void togglePianoEmulation(bool);

    void quantizeSelection();
    void quantizeNtoleDialog();
    void quantizeNtole();

    void setSpeed(QAction*);

    void checkEnableActionsForSelection();
    void toolChanged();
    void copiedEventsChanged();

    void tweakTime();
    void tweakStartTime();
    void tweakEndTime();
    void tweakNote();
    void tweakValue();
    void tweakSmallDecrease();
    void tweakSmallIncrease();
    void tweakMediumDecrease();
    void tweakMediumIncrease();
    void tweakLargeDecrease();
    void tweakLargeIncrease();

    void navigateSelectionUp();
    void navigateSelectionDown();
    void navigateSelectionLeft();
    void navigateSelectionRight();

    void transposeSelectedNotesOctaveUp();
    void transposeSelectedNotesOctaveDown();

  protected:
    void closeEvent(QCloseEvent* event);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* event);

  private:
    MatrixWidget* mw_matrixWidget;
    QScrollBar *vert, *hori;
    ChannelListWidget* channelWidget;
    ProtocolWidget* protocolWidget;
    TrackListWidget* _trackWidget;
    MidiFile* file;
    QString startDirectory, _initFile;
    EventWidget* _eventWidget;
    QSettings* _settings;
    QStringList _recentFilePaths;
    QMenu *_recentPathsMenu, *_deleteChannelMenu,
          *_moveSelectedEventsToTrackMenu, *_moveSelectedEventsToChannelMenu,
          *_pasteToTrackMenu, *_pasteToChannelMenu, *_selectAllFromTrackMenu, *_selectAllFromChannelMenu, * _pasteOptionsMenu;

    QTabWidget* lowerTabWidget;
    QAction *_colorsByChannel, *_colorsByTracks;

    QComboBox *_chooseEditTrack, *_chooseEditChannel;

    QWidget* _miscWidgetControl;
    QGridLayout* _miscControlLayout;

    QComboBox *_miscMode, *_miscController, *_miscChannel;
    QAction *setSingleMode, *setLineMode, *setFreehandMode, *_allChannelsVisible, *_allChannelsInvisible, *_allTracksAudible, *_allTracksMute,
            *_allChannelsAudible, *_allChannelsMute, *_allTracksVisible, *_allTracksInvisible, *stdToolAction, *undoAction, *redoAction, *_pasteAction;
    MiscWidget* _miscWidget;

    QWidget* setupActions(QWidget* parent);
    void rebuildToolbar();
    QAction* getActionById(const QString& actionId);
    QWidget* createCustomToolbar(QWidget* parent);
    QWidget* createSimpleCustomToolbar(QWidget* parent);
    QList<ToolbarActionInfo> getDefaultActionsForPlaceholder();
    void refreshToolbarIcons();

    int _quantizationGrid;
    int quantize(int t, QList<int> ticks);
    QList<QAction*> _activateWithSelections;
    QWidget* _toolbarWidget;
    QMap<QString, QAction*> _actionMap;

    TweakTarget* currentTweakTarget;
    SelectionNavigator* selectionNavigator;
};

#endif
