//#include "dicomtreeitem.h"

//DicomTreeItem::DicomTreeItem(const QList<QVariant> &data, DicomTreeItem *parent)
//{
//    m_parentItem = parent;
//    m_itemData = data;
//}

//void DicomTreeItem::appendChild(DicomTreeItem * child){
//    m_childItems.append(child);
//}


//DicomTreeItem *DicomTreeItem::child(int row){
//    return m_childItems.value(row);
//}

//int DicomTreeItem::childCount() const{
//    return m_childItems.count();
//}

//int DicomTreeItem::row() const{
//    if(m_parentItem)
//        return m_parentItem->m_childItems.indexOf(const_cast<DicomTreeItem*>(this));
//    return 0;
//}

//int DicomTreeItem::columnCount() const{
//    return m_itemData.count();
//}

//QVariant DicomTreeItem::data(int column) const{
//    return m_itemData.value(column);
//}

//DicomTreeItem *DicomTreeItem::parentItem(){
//    return m_parentItem;
//}

//DicomTreeItem::~DicomTreeItem(){
//    qDeleteAll(m_childItems);
//}
