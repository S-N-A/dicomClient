//#ifndef DICOMTREE_H
//#define DICOMTREE_H

//#include <QAbstractItemModel>
//#include <QModelIndex>
//#include <QStringList>
//#include <dicomtreeitem.h>

//class DicomTree: public QAbstractItemModel
//{
//    Q_OBJECT

//public:
//    explicit DicomTree(const QString &data, QObject *parent=nullptr);
//    ~DicomTree() override;

//    QVariant data(const QModelIndex &index, int role) const override;
//    Qt::ItemFlags flags(const QModelIndex &index) const override;
//    QVariant headerData(int section, Qt::Orientation orientation,
//                        int role = Qt::DisplayRole) const override;
//    QModelIndex index(int row, int column,
//                      const QModelIndex &parent = QModelIndex()) const override;
//    QModelIndex parent(const QModelIndex &index) const override;
//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

//private:
//    void setupModelData(const QStringList &lines, DicomTreeItem *parent);

//    DicomTreeItem *rootItem;
//};

//#endif // DICOMTREE_H
