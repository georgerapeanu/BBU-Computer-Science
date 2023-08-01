import { Component, Input, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'app-pagination',
  templateUrl: './pagination.component.html',
  styleUrls: ['./pagination.component.css']
})
export class PaginationComponent {
  @Output() pageChangeEvent = new EventEmitter<number>();
  @Output() pageSizeEvent = new EventEmitter<number>();
  @Input() totalPages: number = 0;
  @Input() currentPage: number = 0;
  @Input() pageNumber: number = 0;
  @Input() pageSize: number = 0;

  setPageNumber(page: number) {
    page = Math.max(page, 0);
    page = Math.min(page, this.totalPages - 1);
    this.pageNumber = page;
    this.pageChangeEvent.emit(page);
  }

  setPageSize(pageSize: number) {
    this.pageSize = pageSize;
    this.pageSizeEvent.emit(pageSize);
  }

  getDisplayedPages() {
    let answer: number[] = [];

    for(let i = 0;i < Math.min(5, this.totalPages);i++) {
      answer.push(i);
    }

    for(let i = Math.max(0, this.totalPages - 5);i < this.totalPages;i++) {
      answer.push(i);
    }

    for(let i = 0;i <= 3;i++) {
      if(this.pageNumber - i >= 0){
        answer.push(this.pageNumber - i);
      }
      if(this.pageNumber + i < this.totalPages) {
        answer.push(this.pageNumber + i);
      }
    }

    answer = answer.sort((n1, n2) => n1 - n2);
    answer = answer.filter((value, index, array) => array.indexOf(value) == index);

    return answer;
  }
}
