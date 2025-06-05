/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:55:58 by atanimot          #+#    #+#             */
/*   Updated: 2025/06/05 13:24:42 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
	{
		return (0);
	}
	initialize_stacks(&stack_a, &stack_b);
	check_and_set(argc, argv, &stack_a, &stack_b);
	// --- stack_a の内容をデバッグ表示 ---
	debug_print_stack_values(stack_a, "Stack A contents");
	// 念のため stack_b も確認 (空のはず)
	// debug_print_stack_values(stack_b, "Stack B contents");
	// --- デバッグ表示終了 ---
	//
	//...(ソート処理など)...
	//
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}

// -----------------------------------------------------------------------------
// 以下は、main から呼び出される関数の実装例 (別の .c ファイルに書くことが多い)
// -----------------------------------------------------------------------------

// void print_error_and_exit(void) {
//     write(STDERR_FILENO, "Error\n", 6);
//     // 必要であればここで確保済みのメモリを解放する処理を入れる
//     // ただし、どこでエラーが起きたかによって解放すべきものが変わるため、
//     // エラー発生箇所で個別に解放処理を書くか、
//     // グローバルなクリーンアップ関数を用意するなどの設計が必要。
//     // ここでは単純にexitします。
//     exit(1);
// }

// t_node *new_node(int value) {
//     t_node *node = (t_node *)malloc(sizeof(t_node));
//     if (!node)
//         return (NULL);
//     node->data = value;
//     node->index = 0; // あとで assign_index などで設定
//     // node->command の初期化も必要ならここで行う
//     node->next = node; // 循環リストなので最初は自分を指す (要素が1つの場合)
//     node->prev = node; // または NULL で初期化し add_node_front/back で設定
//     return (node);
// }

// void add_node_front(t_stack *stack, t_node *new_node) {
//     if (!stack || !new_node)
//         return ;
//     if (stack->top == NULL) { // スタックが空の場合
//         stack->top = new_node;
//         new_node->next = new_node; // 自分自身を指す
//         new_node->prev = new_node; // 自分自身を指す
//     } else {
//         t_node *tail = stack->top->prev; // 末尾要素を取得
//         new_node->next = stack->top;
//         new_node->prev = tail;
//         stack->top->prev = new_node;
//         tail->next = new_node;
//         stack->top = new_node; // topを更新
//     }
//     stack->size++;
// }
