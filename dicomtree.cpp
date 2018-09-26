//#include "dicomtree.h"

//DicomTree::DicomTree(const QString &data, QObject *parent)
//{
//    QList<QVariant> rootData;
//    rootData << "Tag" << "Info";
//    rootItem = new DicomTreeItem(rootData);
//    this->setupModelData(data.split(QString("\n")), rootItem);
//}

//DicomTree::~DicomTree(){
//    delete rootItem;
//}


//QModelIndex DicomTree::index(int row, int column, const QModelIndex &parent)
//            const
//{
//    if (!hasIndex(row, column, parent))
//        return QModelIndex();

//    DicomTreeItem *parentItem;

//    if (!parent.isValid())
//        parentItem = rootItem;
//    else
//        parentItem = static_cast<DicomTreeItem*>(parent.internalPointer());

//    DicomTreeItem *childItem = parentItem->child(row);
//    if (childItem)
//        return createIndex(row, column, childItem);
//    else
//        return QModelIndex();
//}

//QModelIndex DicomTree::parent(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return QModelIndex();

//    DicomTreeItem *childItem = static_cast<DicomTreeItem*>(index.internalPointer());
//    DicomTreeItem *parentItem = childItem->parentItem();

//    if (parentItem == rootItem)
//        return QModelIndex();

//    return createIndex(parentItem->row(), 0, parentItem);
//}

//int DicomTree::rowCount(const QModelIndex &parent) const
//{
//    DicomTreeItem *parentItem;
//    if (parent.column() > 0)
//        return 0;

//    if (!parent.isValid())
//        parentItem = rootItem;
//    else
//        parentItem = static_cast<DicomTreeItem*>(parent.internalPointer());

//    return parentItem->childCount();
//}


//int DicomTree::columnCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return static_cast<DicomTreeItem*>(parent.internalPointer())->columnCount();
//    else
//        return rootItem->columnCount();
//}

//QVariant DicomTree::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    if (role != Qt::DisplayRole)
//        return QVariant();

//    DicomTreeItem *item = static_cast<DicomTreeItem*>(index.internalPointer());

//    return item->data(index.column());
//}

//Qt::ItemFlags DicomTree::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return 0; // suppress warning

//    return QAbstractItemModel::flags(index);
//}


//QVariant DicomTree::headerData(int section, Qt::Orientation orientation,
//                               int role) const
//{
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//        return rootItem->data(section);

//    return QVariant();
//}

